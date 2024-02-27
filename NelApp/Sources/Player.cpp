#include "Player.h"
#include <Enemy.h>
#include <System/Input.h>
#include <Objects/Camera/CameraPlayer.h>
#include <Managers/ModelManager.h>
#include <Managers/SceneManager.h>
#include <Managers/BattleManager.h>
#include <Managers/TextManager.h>
#include <CommandUI.h>

Player::Player()
	: m_fSpeed(0.2f)
	, m_fRotSpeed(1.0f)
	, m_pUI(nullptr)
	, m_nSelect(0)
{
	m_pModel = MODEL_MANAGER.GetModel(ModelManager::MODEL_PLAYER);
	m_pVS = NEW VertexShader();
	m_pVS->Load("Assets/Shaders/VS_Model.cso");
	m_pModel->SetVertexShader(m_pVS);

	GetTransform()->SetScale(Vector3() + 0.1f);
	GetTransform()->SetPosition(Vector3(0.0f, -2.5f, 0.0f));

	// ステータスの設定
	m_pStatus = AddComponent<StatusComponent>();
	m_pStatus->SetName("Player");
	m_pStatus->SetLevel(1);
	m_pStatus->SetHp(100);
	m_pStatus->SetMaxHp(100);
	m_pStatus->SetMp(0);
	m_pStatus->SetMaxMp(0);
	m_pStatus->SetAttack(10);
	m_pStatus->SetDefence(5);
	m_pStatus->SetSpeed(5);
	m_pStatus->SetXp(0);
	m_pStatus->SetMaxXp(100);
	m_pStatus->SetGold(0);
	m_pStatus->SetMagicResistance(0);
	m_pStatus->SetPhysicalResistance(0);

	// 状態
	m_State = STATE_MOVE;

	m_pUI = OBJECTS_MANAGER.AddObjects<CommandUI>();
	m_pUI->SetEnable(false);
}

Player::~Player()
{
	SAFE_DELETE(m_pVS);
}

void Player::Init()
{
}

void Player::Uninit()
{
	m_pUI->Destroy();
}

void Player::Update()
{
	if (m_State == STATE_MOVE) { Move(); }
	if (m_State == STATE_BATTLE) { DrawStatus(); }
	if (IsKeyPress('I')) { m_pStatus->SetHp(0); }

}

void Player::Draw()
{
	if (!m_pCamera) return;
	if (!m_pModel) return;
	DirectX::XMFLOAT4X4 mat[3];
	mat[0] = GetTransform()->GetWorldMatrix();
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	m_pVS->WriteBuffer(0, mat);
	m_pModel->Draw();
}

void Player::DrawStatus()
{
	// ステータスの描画
	TEXT_MANAGER.AddText("Name : " + m_pStatus->GetName(), Vector2(30, 13), 10);
	TEXT_MANAGER.AddText("Level : " + std::to_string(m_pStatus->GetLevel()), Vector2(30, 53), 10);
	TEXT_MANAGER.AddText("HP : " + std::to_string(m_pStatus->GetHp()) + "/" + std::to_string(m_pStatus->GetMaxHp()), Vector2(30, 93), 10);
	TEXT_MANAGER.AddText("MP : " + std::to_string(m_pStatus->GetMp()) + "/" + std::to_string(m_pStatus->GetMaxMp()), Vector2(30, 133), 10);
}

void Player::Damage(int damage)
{
	m_pStatus->SetHp(m_pStatus->GetHp() - damage);
	if (m_pStatus->GetHp() < 0)
	{
		m_pStatus->SetHp(0);
	}
}

void Player::EndBattle()
{
	m_State = STATE_MOVE;
	m_pUI->SetEnable(false);
	m_pEnemies.clear();
}

void Player::Action(int num)
{
	switch (num)
	{
	case CommandUI::COMMAND_TYPE::CMD_ESCAPE:
		m_pUI->FlagDown();
		BATTLE_MANAGER.PlayerEscape();
		break;
	case CommandUI::COMMAND_TYPE::CMD_ATTACK:
		Attack();
		break;
	case CommandUI::COMMAND_TYPE::CMD_DEFENCE:
		Defence();
		// プレイヤーの行動終了
		BATTLE_MANAGER.EndPlayerTurn();
		break;
	case CommandUI::COMMAND_TYPE::CMD_ITEM:
		Item();
		// プレイヤーの行動終了
		BATTLE_MANAGER.EndPlayerTurn();
		break;
	default:
		break;
	}
}

void Player::Move()
{
	if (!m_pCamera) return;

	bool bMove = false;

	Vector3 pos = GetTransform()->GetPosition();
	DirectX::XMFLOAT3 camPos = m_pCamera->GetTransform()->GetPosition3();
	DirectX::XMFLOAT3 camLook = m_pCamera->GetLook().toXMFLOAT3();

	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);
	DirectX::XMVECTOR vCamLook = DirectX::XMLoadFloat3(&camLook);

	DirectX::XMVECTOR vFront;	// カメラの正面方向のベクトル
	vFront = DirectX::XMVectorSubtract(vCamLook, vCamPos);
	vFront = DirectX::XMVector3Normalize(vFront);

	// カメラの右方向のベクトル
	DirectX::XMMATRIX matRotSide = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f));
	DirectX::XMVECTOR vSide = DirectX::XMVector3TransformCoord(vFront, matRotSide);
	DirectX::XMVECTOR vMove = DirectX::XMVectorZero();

	if (IsKeyPress('W')) { bMove = true; vMove = DirectX::XMVectorAdd(vMove, vFront); }
	if (IsKeyPress('S')) { bMove = true; vMove = DirectX::XMVectorSubtract(vMove, vFront); }
	if (IsKeyPress('D')) { bMove = true; vMove = DirectX::XMVectorAdd(vMove, vSide); }
	if (IsKeyPress('A')) { bMove = true; vMove = DirectX::XMVectorSubtract(vMove, vSide); }

	// if (IsKeyPress(VK_SPACE)) { bMove = true; pos.y += m_fSpeed; }
	// if (IsKeyPress(VK_SHIFT)) { bMove = true; pos.y -= m_fSpeed; }

	vMove = DirectX::XMVectorMultiply(vMove, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	vMove = DirectX::XMVector3Normalize(vMove);
	vMove = DirectX::XMVectorScale(vMove, m_fSpeed);

	// カメラの正面方向にモデルを向ける
	// 現在向いている方向
	QUATERNION pRot = GetTransform()->GetRotation();
	QUATERNION Forward;
	float angle = static_cast<CameraPlayer*>(m_pCamera)->GetRadXZ();
	// ラジアンから角度に変換
	angle = RAD2DEG(angle) + 180.0f;
	Forward = Forward.AngleAxis(angle, Vector3::up());

	// 回転の設定
	GetTransform()->SetRotation(Forward);

	// 0.3%の確率で敵とエンカウント
	if (bMove) {
		if (rand() % 1000 < 10) {
			BATTLE_MANAGER.BattleStart(); m_pUI->SetEnable(true);
		}
	}

	// 座標の更新
	DirectX::XMFLOAT3 move;
	DirectX::XMStoreFloat3(&move, vMove);
	pos.x += move.x; pos.y += move.y; pos.z += move.z;
	GetTransform()->SetPosition(pos);
}

void Player::Attack()
{
	if (IsKeyPress('A')) { m_nSelect--; }
	if (IsKeyPress('D')) { m_nSelect++; }
	if (m_nSelect <= 0) { m_nSelect = 0; }
	if (m_nSelect >= m_pEnemies.size()) { m_nSelect = m_pEnemies.size(); }

	if (IsKeyPress(VK_RETURN))
	{
		m_pEnemies[m_nSelect]->Damage(m_pStatus->GetAttack());
		std::string str = m_pEnemies[m_nSelect]->GetName() + "に" + std::to_string(m_pStatus->GetAttack()) + "ダメージ！";
		TEXT_MANAGER.AddText(str, Vector2(500.0f, 500.0f), 60);
	}
}

void Player::Defence()
{
	m_pStatus->SetDefence(10);
	TEXT_MANAGER.AddText("プレイヤーは守りを固めた！", Vector2(500.0f, 500.0f), 60);
	m_pUI->FlagDown();
}

void Player::Item()
{
	m_pUI->FlagDown();
}

