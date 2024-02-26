#pragma once

// ====== インクルード部 ======
#include <Objects/Object.h>
#include <vector>
#include <algorithm>
#include <System/VECTOR.h>
#include <Managers/TextureManager.h>
#include <DirectX/Shader.h>
#include <System/Model.h>

// ====== 前方宣言 ======
using namespace std;

// ====== クラス宣言 ======
class Field : public Object
{
public:	// enum
	enum mapType
	{
		Wall = 0,	// 壁
		Room,		// 部屋
		Route,		// 通路
		Stairs,		// 階段
		Chara,		// キャラクター
	};

	enum mapDir
	{
		Vertical = 0,	// 縦
		Horizontal,		// 横
	};

public:
	// コンストラクタ
	Field();
	// デストラクタ
	~Field();

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;


private:
	void map(int w, int h);

	// 領域外かどうかの判定
	bool IsOutOfRange(int x, int y);

	// 要素の取得
	int GetElement(int x, int y);

	// 要素の書き換え
	void Set(int x, int y, int v);

	// 範囲内のすべてを書き換える
	void SetAll(int left, int top, int right, int bottom, int v);

	// 区間分割
	// 上下左右の座標と部屋番号を取得
	void DivideArea(int left, int top, int right, int bottom, int room);

	// 分割する線
	// 始点のxy座標、終点のxy座標、方向 0-> ver 1-> hor
	void DivideLine(int sx, int sy, int tx, int ty, int dir);

	// 部屋を作成
	void InsertDivideRoom(int left, int top, int right, int bottom);

	// 乱数の取得
	// s以上t未満の乱数を取得
	int GetRandom(int s, int t);

	// 区間を分割する
	void AreaDivide();

	// 分割した区間に小さい部屋を入れる
	void CreateRoom();

	// 部屋から通路を延ばす
	// 通路はマップに書き込む
	void CreateRoute();

	// 穴掘りアルゴリズム
	void DigHole(int x, int y);

	// 穴掘り開始
	void DigHoleStart(int width, int height, int sx, int sy);

	// 分割法開始
	void DivideStart(int width, int height);

	// ランダムな部屋の一つに階段を配置する
	void SetStairs();

	// キャラクターの配置
	void SetChara();

	// マップの端を壁にする
	void SetWall();

private: // メンバ変数
	int m_width;                        // 幅
	int m_height;                       // 高さ
	int m_outOfRange;                   // 範囲外
	vector<vector<int>> m_map;          // マップ
	vector<vector<int>> m_divideArea;	// 区間分割(領域)
	vector<vector<int>> m_divideLine;	// 区間分割(線)
	vector<vector<int>> m_divideRoom;	// 区間分割(部屋)
	bool m_isStart;                     // 開始フラグ
	Vector3 m_StartPos;                 // 開始位置
	Vector3 m_EndPos;                   // 終了位置
	Texture* m_pWall;					// テクスチャ
	Texture* m_pFloor;					// テクスチャ
	PixelShader* m_pPS;					// ピクセルシェーダー
	VertexShader* m_pVS;				// 頂点シェーダー
	Model* m_pModel;					// モデル
};
