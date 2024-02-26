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
	TransformComponent(Object* owner);

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
	Vector3 GetPosition() { return m_position; }
	Vector3 GetOldPosition() { return m_oldPosition; }
	DirectX::XMFLOAT3 GetPosition3() { return DirectX::XMFLOAT3(m_position.x, m_position.y, m_position.z); }
	DirectX::XMFLOAT3 GetOldPosition3() { return DirectX::XMFLOAT3(m_oldPosition.x, m_oldPosition.y, m_oldPosition.z); }

	// �ʒu�̐ݒ�
	void SetPosition(Vector3 position) { m_oldPosition = m_position; m_position = position; }
	void SetPosition(float x, float y, float z) { m_oldPosition = m_position; m_position = Vector3(x, y, z); }
	void SetPosition(DirectX::XMFLOAT3 position) { m_oldPosition = m_position; m_position = Vector3(position.x, position.y, position.z); }

	// ��]�̎擾
	QUATERNION GetRotation() { return m_rotation; }
	QUATERNION GetOldRotation() { return m_oldRotation; }

	// ��]�̐ݒ�
	void SetRotation(QUATERNION rotation) { m_oldRotation = m_rotation; m_rotation = rotation; }
	void SetRotation(float x, float y, float z, float w) { m_oldRotation = m_rotation; m_rotation = QUATERNION(x, y, z, w); }

	// �X�P�[���̎擾
	Vector3 GetScale() { return m_scale; }
	Vector3 GetOldScale() { return m_oldScale; }

	// �X�P�[���̐ݒ�
	void SetScale(Vector3 scale) { m_oldScale = m_scale; m_scale = scale; }
	void SetScale(float x, float y, float z) { m_oldScale = m_scale; m_scale = Vector3(x, y, z); }

	// ���[�J���s��̎擾
	DirectX::XMFLOAT4X4 GetLocalMatrix();
	// ���[���h�s��̎擾
	DirectX::XMFLOAT4X4 GetWorldMatrix();

	// �ړ�����֐�
	void translate(Vector3 move);
	void translate(float x, float y, float z);

	// ��]����֐�
	void rotate(QUATERNION rotate);
	void rotate(float x, float y, float z);

	// �g�傷��֐�
	void scale(Vector3 scale);
	void scale(float x, float y, float z);

private:
	// �ʒu
	Vector3 m_position;
	Vector3 m_oldPosition;
	// ��]
	QUATERNION m_rotation;
	QUATERNION m_oldRotation;
	// �X�P�[��
	Vector3 m_scale;
	Vector3 m_oldScale;

	// ���[�J���s��
	DirectX::XMFLOAT4X4 m_localMatrix;

	// ���[���h�s��
	DirectX::XMFLOAT4X4 m_worldMatrix;
};