#pragma once
// ====== インクルード部 ======
#include <string>
#include <Components/Component.h>

// ====== 前方宣言 ======

// ====== クラスの宣言 ======
class StatusComponent : public Component
{
public:
	struct Status
	{
		std::string name;
		int level;
		int hp;
		int maxHp;
		int mp;
		int maxMp;
		float attack;
		float defence;
		float speed;
		float xp;
		float maxXp;
		int gold;
		float physicalResistance;
		float magicResistance;

		// コンストラクタ
		Status()
		{
			name = "";
			level = 1;
			hp = 0;
			maxHp = 0;
			mp = 0;
			maxMp = 0;
			attack = 0.0f;
			defence = 0.0f;
			speed = 0.0f;
			xp = 0.0f;
			maxXp = 0.0f;
			gold = 0;
			physicalResistance = 0.0f;
			magicResistance = 0.0f;
		}
	};

public:
	// コンストラクタ
	StatusComponent(Object* pObject);

	// デストラクタ
	~StatusComponent() {}

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	// レベルの設定
	void SetLevel(int level) { m_Status.level = level; }

	// レベルの取得
	int GetLevel() { return m_Status.level; }

	// HPの設定
	void SetHp(int hp) { m_Status.hp = hp; }

	// HPの取得
	int GetHp() { return m_Status.hp; }

	// 最大HPの設定
	void SetMaxHp(int maxHp) { m_Status.maxHp = maxHp; }

	// 最大HPの取得
	int GetMaxHp() { return m_Status.maxHp; }

	// MPの設定
	void SetMp(int mp) { m_Status.mp = mp; }

	// MPの取得
	int GetMp() { return m_Status.mp; }

	// 最大MPの設定
	void SetMaxMp(int maxMp) { m_Status.maxMp = maxMp; }

	// 最大MPの取得
	int GetMaxMp() { return m_Status.maxMp; }

	// 攻撃力の設定
	void SetAttack(float attack) { m_Status.attack = attack; }

	// 攻撃力の取得
	float GetAttack() { return m_Status.attack; }

	// 防御力の設定
	void SetDefence(float defence) { m_Status.defence = defence; }

	// 防御力の取得
	float GetDefence() { return m_Status.defence; }

	// スピードの設定
	void SetSpeed(float speed) { m_Status.speed = speed; }

	// スピードの取得
	float GetSpeed() { return m_Status.speed; }

	// 経験値の設定
	void SetXp(float xp) { m_Status.xp = xp; }

	// 経験値の取得
	float GetXp() { return m_Status.xp; }

	// 最大経験値の設定
	void SetMaxXp(float maxXp) { m_Status.maxXp = maxXp; }

	// 最大経験値の取得
	float GetMaxXp() { return m_Status.maxXp; }

	// ゴールドの設定
	void SetGold(int gold) { m_Status.gold = gold; }

	// ゴールドの取得
	int GetGold() { return m_Status.gold; }

	// 物理耐性の設定
	void SetPhysicalResistance(float physicalResistance) { m_Status.physicalResistance = physicalResistance; }

	// 物理耐性の取得
	float GetPhysicalResistance() { return m_Status.physicalResistance; }

	// 魔法耐性の設定
	void SetMagicResistance(float magicResistance) { m_Status.magicResistance = magicResistance; }

	// 魔法耐性の取得
	float GetMagicResistance() { return m_Status.magicResistance; }

	// 名前の設定
	void SetName(std::string name) { m_Status.name = name; }

	// 名前の取得
	std::string GetName() { return m_Status.name; }

private:
	// ステータス
	Status m_Status;
};