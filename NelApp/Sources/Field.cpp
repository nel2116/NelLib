#include <random>
#include "Field.h"
#include <System/VECTOR.h>
#include <System/Geometory.h>
#include <System/Input.h>
#include <Managers/ObjectsManager.h>
#include <Managers/SceneManager.h>
#include <Managers/ModelManager.h>
#include <Player.h>

#define BLOCK_SIZE 5.0f

Field::Field()
	: m_width(33)
	, m_height(33)
	, m_outOfRange(-1)
	, m_isStart(false)
{
	// テクスチャ
	m_pWall = TEXTURE_MANAGER.GetTexture(TextureManager::TEX_WALL);
	m_pFloor = TEXTURE_MANAGER.GetTexture(TextureManager::TEX_FLOOR);

	// シェーダー
	m_pPS = NEW PixelShader();
	m_pPS->Load("Assets/Shaders/Geometry.cso");
	m_pVS = NEW VertexShader();
	m_pVS->Load("Assets/Shaders/VS_Model.cso");

	// モデル
	m_pModel = MODEL_MANAGER.GetModel(ModelManager::MODEL_STAIRS);

	// シェーダー設定
	Geometory::SetPixelShader(m_pPS);
	m_pModel->SetVertexShader(m_pVS);
}

Field::~Field()
{
	SAFE_DELETE(m_pPS);
	SAFE_DELETE(m_pVS);
}

void Field::Init()
{
	int startX = GetRandom(0, m_width - 2);
	int startY = GetRandom(0, m_height - 2);
	if (startY % 2 == 0)++startY;
	if (startX % 2 == 0)++startX;
	map(m_width, m_height);
	DivideStart(m_width, m_height);
	// DigHoleStart(m_width, m_height, startX, startY);
	m_isStart = true;
}

void Field::Uninit()
{
}

void Field::Update()
{
	// カメラがない場合は処理しない
	if (!m_pCamera)return;

	TransformComponent* ts = OBJECTS_MANAGER.GetObjects<Player>()->GetTransform();
	if (m_isStart)
	{
		ts->SetPosition(m_StartPos);
		m_isStart = false;
	}
	// キャラクターが階段に到達したら初期化
	// ブロックの大きさ分誤差を考慮する
	if (ts->GetPosition().x > m_EndPos.x - (BLOCK_SIZE / 2.0f + 0.5f) && ts->GetPosition().x < m_EndPos.x + (BLOCK_SIZE / 2.0f + 0.5f) &&
		ts->GetPosition().z > m_EndPos.z - (BLOCK_SIZE / 2.0f + 0.5f) && ts->GetPosition().z < m_EndPos.z + (BLOCK_SIZE / 2.0f + 0.5f))
	{
		SCENE_MANAGER.ResetScene();
	}
	// すべての壁との当たり判定
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_map[i][j] == Wall)
			{
				// もしも当たっていたら、プレイヤーを元の位置に戻す
				if (ts->GetPosition().x > j * BLOCK_SIZE - (BLOCK_SIZE / 2.0f + 0.5f) && ts->GetPosition().x < j * BLOCK_SIZE + (BLOCK_SIZE / 2.0f + 0.5f) &&
					ts->GetPosition().z > i * BLOCK_SIZE - (BLOCK_SIZE / 2.0f + 0.5f) && ts->GetPosition().z < i * BLOCK_SIZE + (BLOCK_SIZE / 2.0f + 0.5f))
				{
					ts->SetPosition(ts->GetOldPosition());
				}
			}
		}
	}
}

void Field::Draw()
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_map[i][j] == Wall)
			{
				Geometory::SetTexture(m_pWall);
				Geometory::DrawTexBox(Vector3(j * BLOCK_SIZE, 0.5f * BLOCK_SIZE, i * BLOCK_SIZE).toXMFLOAT3(), Vector3(1.0f * BLOCK_SIZE, 2.0f * BLOCK_SIZE, 1.0f * BLOCK_SIZE).toXMFLOAT3(), Vector4(0.1f, 0.1f, 0.1f, 1.0f).toXMFLOAT4());
			}
			else if (m_map[i][j] != Stairs)
			{
				Geometory::SetTexture(m_pFloor);
				Geometory::DrawTexBox(Vector3(j * BLOCK_SIZE, -1.0f * BLOCK_SIZE, i * BLOCK_SIZE).toXMFLOAT3(), Vector3(1.0f * BLOCK_SIZE, 1.0f * BLOCK_SIZE, 1.0f * BLOCK_SIZE).toXMFLOAT3(), Vector4(0.1f, 0.1f, 0.1f, 1.0f).toXMFLOAT4());
				Geometory::DrawTexBox(Vector3(j * BLOCK_SIZE, 2.0f * BLOCK_SIZE, i * BLOCK_SIZE).toXMFLOAT3(), Vector3(1.0f * BLOCK_SIZE, 1.0f * BLOCK_SIZE, 1.0f * BLOCK_SIZE).toXMFLOAT3(), Vector4(0.1f, 0.1f, 0.1f, 1.0f).toXMFLOAT4());
			}
			else
			{// 階段
				DirectX::XMFLOAT4X4 mat[3];
				DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(m_EndPos.x, m_EndPos.y, m_EndPos.z);
				world = DirectX::XMMatrixTranspose(world);
				DirectX::XMStoreFloat4x4(&mat[0], world);
				mat[1] = m_pCamera->GetViewMatrix();
				mat[2] = m_pCamera->GetProjectionMatrix();

				m_pVS->WriteBuffer(0, mat);
				m_pModel->Draw();
				Geometory::DrawTexBox(Vector3(j * BLOCK_SIZE, 2.0f * BLOCK_SIZE, i * BLOCK_SIZE).toXMFLOAT3(), Vector3(1.0f * BLOCK_SIZE, 1.0f * BLOCK_SIZE, 1.0f * BLOCK_SIZE).toXMFLOAT3(), Vector4(0.1f, 0.1f, 0.1f, 1.0f).toXMFLOAT4());
			}
		}
	}
}

void Field::map(int w, int h)
{
	m_width = w;
	m_height = h;
	m_outOfRange = -1;

	// マップの初期化
	m_map.resize(m_height);
	for (int i = 0; i < m_height; ++i)
	{
		m_map[i].resize(m_width);
		for (int j = 0; j < m_width; ++j)
		{
			m_map[i][j] = Wall;
		}
	}
}

bool Field::IsOutOfRange(int x, int y)
{
	return (x < 0 || x >= m_width || y < 0 || y >= m_height);
}

int Field::GetElement(int x, int y)
{
	if (IsOutOfRange(x, y))
	{
		return m_outOfRange;
	}
	return m_map[y][x];
}

void Field::Set(int x, int y, int v)
{
	if (IsOutOfRange(x, y))
	{
		return;
	}
	m_map[y][x] = v;
}

void Field::SetAll(int left, int top, int right, int bottom, int v)
{
	for (int y = top; y <= bottom; ++y)
	{
		for (int x = left; x <= right; ++x)
		{
			Set(x, y, v);
		}
	}
}

void Field::DivideArea(int left, int top, int right, int bottom, int room)
{
	m_divideArea.emplace_back();
	int size = m_divideArea.size();
	m_divideArea[size - 1].emplace_back(left);
	m_divideArea[size - 1].emplace_back(top);
	m_divideArea[size - 1].emplace_back(right);
	m_divideArea[size - 1].emplace_back(bottom);
	m_divideArea[size - 1].emplace_back(room);
}

void Field::DivideLine(int sx, int sy, int tx, int ty, int dir)
{
	m_divideLine.emplace_back();
	int size = m_divideLine.size();
	m_divideLine[size - 1].emplace_back(sx);
	m_divideLine[size - 1].emplace_back(sy);
	m_divideLine[size - 1].emplace_back(tx);
	m_divideLine[size - 1].emplace_back(ty);
	m_divideLine[size - 1].emplace_back(dir);
}

void Field::InsertDivideRoom(int left, int top, int right, int bottom)
{
	m_divideRoom.emplace_back();
	int size = m_divideRoom.size();
	m_divideRoom[size - 1].emplace_back(left);
	m_divideRoom[size - 1].emplace_back(top);
	m_divideRoom[size - 1].emplace_back(right);
	m_divideRoom[size - 1].emplace_back(bottom);
}

int Field::GetRandom(int s, int t)
{
	// 乱数の生成
	random_device rand;		// 乱数デバイス
	mt19937 mt(rand());		// 乱数生成エンジン
	if (s > t)swap(s, t);	// sがtより大きい場合は入れ替え
	uniform_int_distribution<int> randInt(s, t);	// 一様乱数
	return randInt(mt);
}

void Field::AreaDivide()
{
	int lowerWidth = 0;
	int upperWidth = m_width - 1;
	int lowerHeight = 0;
	int upperHeight = m_height - 1;
	int roomID = 0;
	vector<vector<int>> line;	// 線の情報

	bool isVertical;
	if (GetRandom(0, 1) & 1)isVertical = true;
	else isVertical = false;

	while (true)
	{
		// 分割できない条件
		if (upperWidth - lowerWidth < 6 || upperHeight - lowerHeight < 6)break;

		// 部屋が指定した数に達したら
		if (roomID >= 10)break;

		// この座標において分割線を引く
		int dividePoint;

		// 縦に分割
		if (isVertical)
		{
			// 分割する座標を決定
			dividePoint = GetRandom(lowerWidth + 6 + 2, upperWidth - 6 - 2);

			// 過去の線と重なるか隣接した場合やり直し
			bool isOverlap = false;
			for (auto v : line)
			{
				int sx = v[0];
				int sy = v[1];
				int tx = v[2];
				int ty = v[3];
				int dir = v[4];

				if (dir == Vertical)
				{
					if (sx == dividePoint || tx == dividePoint)
					{
						if (sy <= lowerHeight + 1 && ty >= upperHeight - 1)
						{
							isOverlap = true;
							break;
						}
					}
				}
				else
				{
					if (sx <= lowerWidth + 1 && tx >= upperWidth - 1)
					{
						if (sy == dividePoint || ty == dividePoint)
						{
							isOverlap = true;
							break;
						}
					}
				}
			}
			if (isOverlap)continue;

			// 分割する
			if ((upperWidth + lowerWidth / 2 < dividePoint))
			{
				DivideArea(dividePoint + 2, lowerHeight + 1, upperWidth - 1, upperHeight - 1, roomID);
				upperWidth = dividePoint - 1;
			}
			else
			{
				DivideArea(lowerWidth + 1, lowerHeight + 1, dividePoint - 2, upperHeight - 1, roomID);
				lowerWidth = dividePoint + 1;
			}
			// 線を引く
			DivideLine(dividePoint, lowerHeight, dividePoint, upperHeight - 1, Vertical);
			isVertical = false;

			// 線の情報を保存
			line.emplace_back();
			int size = line.size();
			line[size - 1].emplace_back(dividePoint);
			line[size - 1].emplace_back(lowerHeight);
			line[size - 1].emplace_back(dividePoint);
			line[size - 1].emplace_back(upperHeight - 1);
			line[size - 1].emplace_back(Vertical);
		}
		// 横に分割
		else
		{
			dividePoint = GetRandom(lowerHeight + 6 + 2, upperHeight - 6 - 2);
			if ((upperHeight + lowerHeight / 2 < dividePoint))
			{
				DivideArea(lowerWidth + 1, dividePoint + 2, upperWidth - 1, upperHeight - 1, roomID);
				upperHeight = dividePoint - 1;
			}
			else if ((upperHeight + lowerHeight / 2 > dividePoint))
			{
				DivideArea(lowerWidth + 1, lowerHeight + 1, upperWidth - 1, dividePoint - 2, roomID);
				lowerHeight = dividePoint + 1;
			}

			DivideLine(lowerWidth, dividePoint, upperWidth - 1, dividePoint, Horizontal);
			isVertical = true;

			// 線の情報を保存
			line.emplace_back();
			int size = line.size();
			line[size - 1].emplace_back(lowerWidth);
			line[size - 1].emplace_back(dividePoint);
			line[size - 1].emplace_back(upperWidth - 1);
			line[size - 1].emplace_back(dividePoint);
			line[size - 1].emplace_back(Horizontal);
		}
		++roomID;
	}
}

// 部屋を作成
void Field::CreateRoom()
{
	// 区画の中に部屋を作成する
	// 部屋同士は1マス以上離す
	for (auto v : m_divideArea)
	{
		int left = v[0];
		int top = v[1];
		int right = v[2];
		int bottom = v[3];
		int roomID = v[4];

		// 部屋の大きさを決定, 5x5以上
		// 部屋は区画より小さい
		int roomWidth = GetRandom(5, right - left - 1);
		int roomHeight = GetRandom(5, bottom - top - 1);

		// 部屋の左上の座標を決定
		int roomLeft = GetRandom(left + 1, right - roomWidth - 1);
		int roomTop = GetRandom(top + 1, bottom - roomHeight - 1);

		// 部屋の右下の座標を決定
		int roomRight = roomLeft + roomWidth;
		int roomBottom = roomTop + roomHeight;

		// 部屋を作成
		InsertDivideRoom(roomLeft, roomTop, roomRight, roomBottom);
	}

	// 部屋を重ならないようにする
	// また、部屋同士は1マス以上離す
	for (int i = 0; i < m_divideRoom.size(); ++i)
	{
		for (int j = i + 1; j < m_divideRoom.size(); ++j)
		{
			auto roomBefore = m_divideRoom[i];
			auto roomAfter = m_divideRoom[j];

			int leftBefore = roomBefore[0];
			int topBefore = roomBefore[1];
			int rightBefore = roomBefore[2];
			int bottomBefore = roomBefore[3];

			int leftAfter = roomAfter[0];
			int topAfter = roomAfter[1];
			int rightAfter = roomAfter[2];
			int bottomAfter = roomAfter[3];

			// 部屋同士が重なっている場合
			if (leftBefore < rightAfter && rightBefore > leftAfter && topBefore < bottomAfter && bottomBefore > topAfter)
			{
				// 重なっている部分を削除
				if (leftBefore < leftAfter)
				{
					rightBefore = leftAfter - 1;
				}
				else if (leftBefore > leftAfter)
				{
					leftBefore = rightAfter + 1;
				}

				if (topBefore < topAfter)
				{
					bottomBefore = topAfter - 1;
				}
				else if (topBefore > topAfter)
				{
					topBefore = bottomAfter + 1;
				}

				// 部屋を再設定
				m_divideRoom[i][0] = leftBefore;
				m_divideRoom[i][1] = topBefore;
				m_divideRoom[i][2] = rightBefore;
				m_divideRoom[i][3] = bottomBefore;
			}
		}
	}
}

// 部屋から通路を延ばす
// DigHoleは使わない
void Field::CreateRoute()
{
	int cnt = 0;
	int size = m_divideRoom.size() - 1;

	for (auto v : m_divideLine)
	{
		// 通路数は部屋数+1であるため、最後の通路は無視する
		if (cnt >= size)break;

		int sx = v[0];
		int sy = v[1];
		int tx = v[2];
		int ty = v[3];
		int dir = v[4];

		// 部屋情報
		auto roomBefore = m_divideRoom[cnt];
		auto roomAfter = m_divideRoom[cnt + 1];

		int leftBefore = roomBefore[0];
		int topBefore = roomBefore[1];
		int rightBefore = roomBefore[2];
		int bottomBefore = roomBefore[3];

		int leftAfter = roomAfter[0];
		int topAfter = roomAfter[1];
		int rightAfter = roomAfter[2];
		int bottomAfter = roomAfter[3];

		// 縦に線が引かれている場合
		if (dir == Vertical)
		{
			// 部屋のどこから線を伸ばすのかを決定。
			int routeBefore = GetRandom(topBefore + 1, bottomBefore - 1);
			int routeAfter = GetRandom(topAfter + 1, bottomAfter - 1);

			// 線を挟んで2つの部屋がどちらにあるかで場合分け
			if (leftBefore < leftAfter)
			{
				SetAll(rightBefore, routeBefore, sx, routeBefore, Route);
				SetAll(sx, routeAfter, leftAfter, routeAfter, Route);
			}
			else
			{
				SetAll(rightAfter, routeAfter, sx, routeAfter, Route);
				SetAll(sx, routeBefore, leftBefore, routeBefore, Route);
			}

			// 伸ばした線の間を結ぶ
			if (routeBefore > routeAfter) swap(routeBefore, routeAfter);
			SetAll(sx, routeBefore, sx, routeAfter, Route);
		}
		else
		{
			// 部屋のどこから線を伸ばすのかを決定。
			int routeBefore = GetRandom(leftBefore + 1, rightBefore - 1);
			int routeAfter = GetRandom(leftAfter + 1, rightAfter - 1);

			// 線を挟んで2つの部屋がどちらにあるかで場合分け
			if (topBefore < topAfter)
			{
				SetAll(routeBefore, bottomBefore, routeBefore, sy, Route);
				SetAll(routeAfter, sy, routeAfter, topAfter, Route);
			}
			else
			{
				SetAll(routeAfter, bottomAfter, routeAfter, sy, Route);
				SetAll(routeBefore, sy, routeBefore, topBefore, Route);
			}

			// 伸ばした線の間を結ぶ
			if (routeBefore > routeAfter) swap(routeBefore, routeAfter);
			SetAll(routeBefore, sy, routeAfter, sy, Route);
		}
		++cnt;
	}
}


void Field::DigHole(int x, int y)
{
	Set(x, y, Route);

	int moveX[4] = { 0, 0, -1, 1 };
	int moveY[4] = { 1, -1, 0, 0 };
	vector<int> act = { 0, 1, 2, 3 };

	// 行動順をランダムにする
	random_device get_rand_dev;
	mt19937 mt(get_rand_dev());
	shuffle(act.begin(), act.end(), mt);

	for (auto a : act)
	{
		int dx = moveX[a];
		int dy = moveY[a];

		if (GetElement(x + dx * 2, y + dy * 2) == Wall)
		{
			Set(x + dx, y + dy, Route);
			DigHole(x + dx * 2, y + dy * 2);
		}
	}
}

void Field::DigHoleStart(int width, int height, int sx, int sy)
{
	int xStart = sx;
	int yStart = sy;
	DigHole(xStart, yStart);
}

void Field::DivideStart(int width, int height)
{
	// 区画分割
	AreaDivide();

	// 区画に部屋を作成
	CreateRoom();

	// 部屋から通路を延ばす
	CreateRoute();

	// 部屋
	for (auto a : m_divideRoom)
	{
		SetAll(a[0], a[1], a[2], a[3], Room);
	}

	SetStairs();
	SetChara();
	SetWall();
}

void Field::SetStairs()
{
	auto room = m_divideRoom[0];
	int x = GetRandom(room[0] + 1, room[2] - 1);
	int z = GetRandom(room[1] + 1, room[3] - 1);
	Set(x, z, Stairs);
	m_EndPos = Vector3(x * BLOCK_SIZE, -1.0f * BLOCK_SIZE, z * BLOCK_SIZE);
}

void Field::SetChara()
{
	// ランダムな部屋の一つにキャラクターを配置する
	int size = m_divideRoom.size();
	auto room = m_divideRoom[size - 1];
	int x = GetRandom(room[0] + 1, room[2] - 1);
	int z = GetRandom(room[1] + 1, room[3] - 1);
	Set(x, z, Chara);
	float y = OBJECTS_MANAGER.GetObjects<Player>()->GetTransform()->GetPosition().y;
	m_StartPos = Vector3(x * BLOCK_SIZE, y, z * BLOCK_SIZE);
}

void Field::SetWall()
{
	// マップの端を壁にする
	for (int i = 0; i < m_height; ++i)
	{
		Set(0, i, Wall);
		Set(m_width - 1, i, Wall);
	}
	for (int i = 0; i < m_width; ++i)
	{
		Set(i, 0, Wall);
		Set(i, m_height - 1, Wall);
	}
}

