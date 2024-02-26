#pragma once
// ====== インクルード部 ======
#include <Objects/Object.h>
#include <System/Model.h>
#include <DirectX/Shader.h>
#include <Components/StatusComponent.h>

// ====== 前方宣言 ======
class Enemy;

// ====== クラス宣言 ======
class Player : public Object
{
public:
	enum STATE
	{
		STATE_MOVE,
		STATE_BATTLE,
		STATE_MAX
	};

public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;


	// ダメージ
	void Damage(int damage);

	// 死亡判定
	// true : 死亡
	// false : 生存
	bool IsDead() { return m_pStatus->GetHp() <= 0; }

	// 状態を取得
	STATE GetState() { return m_State; }

	// 状態を設定
	void SetState(STATE state) { m_State = state; }

	// 戦闘終了
	void EndBattle();

	void SetEnemys(std::vector<Enemy*> pEnemies) { m_pEnemies = pEnemies; }

private:
	// 移動
	void Move();

	void Action();

	// ステータスの描画
	void DrawStatus();

private:
	float m_fSpeed;
	float m_fRotSpeed;
	Model* m_pModel;
	VertexShader* m_pVS;
	StatusComponent* m_pStatus;
	STATE m_State;
	std::vector<Enemy*> m_pEnemies;
};