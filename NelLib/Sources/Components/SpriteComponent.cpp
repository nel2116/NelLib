#include "SpriteComponent.h"
#include <DirectXMath.h>
#include <Managers/TextureManager.h>
#include <DirectX/Sprite.h>
#include <DirectX/Renderer.h>
#include <Objects/Camera/CameraUI.h>
#include <Components/TransformComponent.h>

void SpriteComponent::Init()
{
}

void SpriteComponent::Uninit()
{
}

void SpriteComponent::Update()
{
}

void SpriteComponent::Draw()
{
	CameraBase* camera = GetOwner()->GetCamera();    // �J�����̎擾

	// World���
	DirectX::XMFLOAT4X4 world;			                            // �s��̊i�[��
	DirectX::XMFLOAT4X4 view;			                            // �s��̊i�[��
	DirectX::XMFLOAT4X4 projection;			                        // �s��̊i�[��
	world = GetOwner()->GetTransform()->GetWorldMatrix();	        // ���[���h�s��̎擾
	view = camera->GetTransposedViewMatrix();						// �r���[�s��̎擾
	projection = camera->GetTransposedProjectionMatrix();			// �v���W�F�N�V�����s��̎擾

	Sprite::SetWorld(world);	                                    // ���[���h�s��̐ݒ�
	Sprite::SetView(view);			                                // �r���[�s��̐ݒ�
	Sprite::SetProjection(projection);	                            // �v���W�F�N�V�����s��̐ݒ�

	VECTOR size = GetOwner()->GetTransform()->GetScale();	        // �e�N�X�`���̃T�C�Y�̎擾
	Sprite::SetSize(VECTOR2(size.x, size.y));	                    // �T�C�Y�̐ݒ�
	Sprite::SetTexture(m_pTex);			                            // �e�N�X�`���̐ݒ�
	RenderTarget* RTV = RENDERER.GetDefaultRTV();
	RENDERER.SetRenderTargets(1, &RTV, nullptr);
	Sprite::Draw();							                        // �`��
}
