#include "SpriteComponent.h"
#include <DirectXMath.h>
#include <Managers/TextureManager.h>
#include <Managers/CameraManager.h>
#include <DirectX/Sprite.h>
#include <DirectX/Renderer.h>
#include <Components/TransformComponent.h>

SpriteComponent::SpriteComponent(Object* pObject)
	: Component(pObject)
	, m_pCamera(nullptr)
{
}

void SpriteComponent::Init()
{
	m_spriteInfo.texture = TEXTURE_MANAGER.GetTexture(TextureManager::TEX_DEFAULT);   // �e�N�X�`���̎擾
	m_pCamera = CAMERA_MANAGER.GetCamera(CameraManager::E_CAM_UI);		// �J�����̐ݒ�
}

void SpriteComponent::Uninit()
{
}

void SpriteComponent::Update()
{
}

void SpriteComponent::Draw()
{
	// �J�������Ȃ��ꍇ�͕`�悵�Ȃ�
	if (!m_pCamera) { return; }

	// World���
	DirectX::XMFLOAT4X4 world;								// �s��̊i�[��
	DirectX::XMFLOAT4X4 view;								// �s��̊i�[��
	DirectX::XMFLOAT4X4 projection;							// �s��̊i�[��
	world = GetOwner()->GetTransform()->GetWorldMatrix();	// ���[���h�s��̎擾
	view = m_pCamera->GetViewMatrix();						// �r���[�s��̎擾
	projection = m_pCamera->GetProjectionMatrix();			// �v���W�F�N�V�����s��̎擾

	Sprite::SetWorld(world);								// ���[���h�s��̐ݒ�
	Sprite::SetView(view);									// �r���[�s��̐ݒ�
	Sprite::SetProjection(projection);						// �v���W�F�N�V�����s��̐ݒ�

	Sprite::SetColor(m_spriteInfo.color);					// �F�̐ݒ�

	Sprite::SetSize(m_spriteInfo.size);						// �T�C�Y�̐ݒ�
	Sprite::SetOffset(Vector2::zero());						// �I�t�Z�b�g�̐ݒ�

	Sprite::SetUVPos(m_spriteInfo.uvOffset);				// UV���W�̐ݒ�
	Sprite::SetUVScale(m_spriteInfo.uvScale);				// UV�T�C�Y�̐ݒ�

	Sprite::SetTexture(m_spriteInfo.texture);				// �e�N�X�`���̐ݒ�
	RenderTarget* RTV = RENDERER.GetDefaultRTV();
	RENDERER.SetRenderTargets(1, &RTV, nullptr);
	Sprite::Draw();											// �`��
}

void SpriteComponent::SetSizeToTexture()
{
	if (m_spriteInfo.texture)
	{
		// �e�N�X�`���̃T�C�Y���擾
		m_spriteInfo.size.x = (float)m_spriteInfo.texture->GetWidth();
		m_spriteInfo.size.y = (float)m_spriteInfo.texture->GetHeight();

		// �T�C�Y�̐ݒ�
		m_spriteInfo.size *= m_spriteInfo.uvScale;
	}
}

void SpriteComponent::SetSplit(Vector2 split)
{
	// --- �����ݒ�
	m_spriteInfo.uvScale.x = 1.0f / split.x;
	m_spriteInfo.uvScale.y = 1.0f / split.y;

	m_spriteInfo.size.x *= m_spriteInfo.uvScale.x;
	m_spriteInfo.size.y *= m_spriteInfo.uvScale.y;

	m_spriteInfo.splitX = static_cast<int>(split.x);
	m_spriteInfo.splitY = static_cast<int>(split.y);
}

void SpriteComponent::SetIndex(int index)
{
	// --- �C���f�b�N�X�ݒ�
	m_spriteInfo.uvOffset.x = (index % m_spriteInfo.splitX) * m_spriteInfo.uvScale.x;
	m_spriteInfo.uvOffset.y = (index / m_spriteInfo.splitX) * m_spriteInfo.uvScale.y;
}
