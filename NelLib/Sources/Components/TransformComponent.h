#pragma once

// ====== �C���N���[�h ======
#include <Components/Component.h>
#include <DirectXMath.h>
#include <System/VECTOR.h>
#include <System/QUATERNION.h>

// ====== �N���X�̐錾 ======
class TransformComponent : public Component
{
public:
	// �R���X�g���N�^
	TransformComponent(Object* owner)
		: Component(owner)
		, m_position(VECTOR(0.0f, 0.0f, 0.0f))
		, m_rotation(QUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
		, m_scale(VECTOR(1.0f, 1.0f, 1.0f))
		, m_localMatrix(DirectX::XMFLOAT4X4())
		, m_worldMatrix(DirectX::XMFLOAT4X4()) {}

	// �f�X�g���N�^
	~TransformComponent() {}

	// ������
	void Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;

	// �Q�b�^�[�A�Z�b�^�[
	// �ʒu�̎擾
	VECTOR GetPosition() { return m_position; }
	DirectX::XMFLOAT3 GetPosition3() { return DirectX::XMFLOAT3(m_position.x, m_position.y, m_position.z); }

	// �ʒu�̐ݒ�
	void SetPosition(VECTOR position) { m_position = position; }
	void SetPosition(float x, float y, float z) { m_position = VECTOR(x, y, z); }
	void SetPosition(DirectX::XMFLOAT3 position) { m_position = VECTOR(position.x, position.y, position.z); }
	// ��]�̎擾
	QUATERNION GetRotation() { return m_rotation; }
	// ��]�̐ݒ�
	void SetRotation(QUATERNION rotation) { m_rotation = rotation; }
	void SetRotation(float x, float y, float z, float w) { m_rotation = QUATERNION(x, y, z, w); }
	// �X�P�[���̎擾
	VECTOR GetScale() { return m_scale; }
	// �X�P�[���̐ݒ�
	void SetScale(VECTOR scale) { m_scale = scale; }
	void SetScale(float x, float y, float z) { m_scale = VECTOR(x, y, z); }

	// ���[�J���s��̎擾
	DirectX::XMFLOAT4X4 GetLocalMatrix();
	// ���[���h�s��̎擾
	DirectX::XMFLOAT4X4 GetWorldMatrix();

	// �ړ�����֐�
	void translate(VECTOR move);
	void translate(float x, float y, float z);

	// ��]����֐�
	void rotate(QUATERNION rotate);
	void rotate(float x, float y, float z);

	// �g�傷��֐�
	void scale(VECTOR scale);
	void scale(float x, float y, float z);

private:
	// �ʒu
	VECTOR m_position;
	// ��]
	QUATERNION m_rotation;
	// �X�P�[��
	VECTOR m_scale;

	// ���[�J���s��
	DirectX::XMFLOAT4X4 m_localMatrix;

	// ���[���h�s��
	DirectX::XMFLOAT4X4 m_worldMatrix;
};