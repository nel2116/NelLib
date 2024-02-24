#pragma once
// ====== �C���N���[�h�� ======
#include <Objects/Object.h>
#include <System/Model.h>
#include <DirectX/Shader.h>

// ====== �N���X�錾 ======
class Player : public Object
{

public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

private:
	// �ړ�
	void Move();
	float m_fSpeed;
	float m_fRotSpeed;
	Model* m_pModel;
	VertexShader* m_pVS;
};