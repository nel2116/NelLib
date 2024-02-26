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
	// �e�N�X�`��
	m_pWall = TEXTURE_MANAGER.GetTexture(TextureManager::TEX_WALL);
	m_pFloor = TEXTURE_MANAGER.GetTexture(TextureManager::TEX_FLOOR);

	// �V�F�[�_�[
	m_pPS = NEW PixelShader();
	m_pPS->Load("Assets/Shaders/Geometry.cso");
	m_pVS = NEW VertexShader();
	m_pVS->Load("Assets/Shaders/VS_Model.cso");

	// ���f��
	m_pModel = MODEL_MANAGER.GetModel(ModelManager::MODEL_STAIRS);

	// �V�F�[�_�[�ݒ�
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
	// �J�������Ȃ��ꍇ�͏������Ȃ�
	if (!m_pCamera)return;

	TransformComponent* ts = OBJECTS_MANAGER.GetObjects<Player>()->GetTransform();
	if (m_isStart)
	{
		ts->SetPosition(m_StartPos);
		m_isStart = false;
	}
	// �L�����N�^�[���K�i�ɓ��B�����珉����
	// �u���b�N�̑傫�����덷���l������
	if (ts->GetPosition().x > m_EndPos.x - (BLOCK_SIZE / 2.0f + 0.5f) && ts->GetPosition().x < m_EndPos.x + (BLOCK_SIZE / 2.0f + 0.5f) &&
		ts->GetPosition().z > m_EndPos.z - (BLOCK_SIZE / 2.0f + 0.5f) && ts->GetPosition().z < m_EndPos.z + (BLOCK_SIZE / 2.0f + 0.5f))
	{
		SCENE_MANAGER.ResetScene();
	}
	// ���ׂĂ̕ǂƂ̓����蔻��
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_map[i][j] == Wall)
			{
				// �������������Ă�����A�v���C���[�����̈ʒu�ɖ߂�
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
			{// �K�i
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

	// �}�b�v�̏�����
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
	// �����̐���
	random_device rand;		// �����f�o�C�X
	mt19937 mt(rand());		// ���������G���W��
	if (s > t)swap(s, t);	// s��t���傫���ꍇ�͓���ւ�
	uniform_int_distribution<int> randInt(s, t);	// ��l����
	return randInt(mt);
}

void Field::AreaDivide()
{
	int lowerWidth = 0;
	int upperWidth = m_width - 1;
	int lowerHeight = 0;
	int upperHeight = m_height - 1;
	int roomID = 0;
	vector<vector<int>> line;	// ���̏��

	bool isVertical;
	if (GetRandom(0, 1) & 1)isVertical = true;
	else isVertical = false;

	while (true)
	{
		// �����ł��Ȃ�����
		if (upperWidth - lowerWidth < 6 || upperHeight - lowerHeight < 6)break;

		// �������w�肵�����ɒB������
		if (roomID >= 10)break;

		// ���̍��W�ɂ����ĕ�����������
		int dividePoint;

		// �c�ɕ���
		if (isVertical)
		{
			// ����������W������
			dividePoint = GetRandom(lowerWidth + 6 + 2, upperWidth - 6 - 2);

			// �ߋ��̐��Əd�Ȃ邩�אڂ����ꍇ��蒼��
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

			// ��������
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
			// ��������
			DivideLine(dividePoint, lowerHeight, dividePoint, upperHeight - 1, Vertical);
			isVertical = false;

			// ���̏���ۑ�
			line.emplace_back();
			int size = line.size();
			line[size - 1].emplace_back(dividePoint);
			line[size - 1].emplace_back(lowerHeight);
			line[size - 1].emplace_back(dividePoint);
			line[size - 1].emplace_back(upperHeight - 1);
			line[size - 1].emplace_back(Vertical);
		}
		// ���ɕ���
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

			// ���̏���ۑ�
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

// �������쐬
void Field::CreateRoom()
{
	// ���̒��ɕ������쐬����
	// �������m��1�}�X�ȏ㗣��
	for (auto v : m_divideArea)
	{
		int left = v[0];
		int top = v[1];
		int right = v[2];
		int bottom = v[3];
		int roomID = v[4];

		// �����̑傫��������, 5x5�ȏ�
		// �����͋���菬����
		int roomWidth = GetRandom(5, right - left - 1);
		int roomHeight = GetRandom(5, bottom - top - 1);

		// �����̍���̍��W������
		int roomLeft = GetRandom(left + 1, right - roomWidth - 1);
		int roomTop = GetRandom(top + 1, bottom - roomHeight - 1);

		// �����̉E���̍��W������
		int roomRight = roomLeft + roomWidth;
		int roomBottom = roomTop + roomHeight;

		// �������쐬
		InsertDivideRoom(roomLeft, roomTop, roomRight, roomBottom);
	}

	// �������d�Ȃ�Ȃ��悤�ɂ���
	// �܂��A�������m��1�}�X�ȏ㗣��
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

			// �������m���d�Ȃ��Ă���ꍇ
			if (leftBefore < rightAfter && rightBefore > leftAfter && topBefore < bottomAfter && bottomBefore > topAfter)
			{
				// �d�Ȃ��Ă��镔�����폜
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

				// �������Đݒ�
				m_divideRoom[i][0] = leftBefore;
				m_divideRoom[i][1] = topBefore;
				m_divideRoom[i][2] = rightBefore;
				m_divideRoom[i][3] = bottomBefore;
			}
		}
	}
}

// ��������ʘH�����΂�
// DigHole�͎g��Ȃ�
void Field::CreateRoute()
{
	int cnt = 0;
	int size = m_divideRoom.size() - 1;

	for (auto v : m_divideLine)
	{
		// �ʘH���͕�����+1�ł��邽�߁A�Ō�̒ʘH�͖�������
		if (cnt >= size)break;

		int sx = v[0];
		int sy = v[1];
		int tx = v[2];
		int ty = v[3];
		int dir = v[4];

		// �������
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

		// �c�ɐ���������Ă���ꍇ
		if (dir == Vertical)
		{
			// �����̂ǂ��������L�΂��̂�������B
			int routeBefore = GetRandom(topBefore + 1, bottomBefore - 1);
			int routeAfter = GetRandom(topAfter + 1, bottomAfter - 1);

			// ���������2�̕������ǂ���ɂ��邩�ŏꍇ����
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

			// �L�΂������̊Ԃ�����
			if (routeBefore > routeAfter) swap(routeBefore, routeAfter);
			SetAll(sx, routeBefore, sx, routeAfter, Route);
		}
		else
		{
			// �����̂ǂ��������L�΂��̂�������B
			int routeBefore = GetRandom(leftBefore + 1, rightBefore - 1);
			int routeAfter = GetRandom(leftAfter + 1, rightAfter - 1);

			// ���������2�̕������ǂ���ɂ��邩�ŏꍇ����
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

			// �L�΂������̊Ԃ�����
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

	// �s�����������_���ɂ���
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
	// ��敪��
	AreaDivide();

	// ���ɕ������쐬
	CreateRoom();

	// ��������ʘH�����΂�
	CreateRoute();

	// ����
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
	// �����_���ȕ����̈�ɃL�����N�^�[��z�u����
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
	// �}�b�v�̒[��ǂɂ���
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

