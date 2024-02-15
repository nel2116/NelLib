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
	CameraBase* camera = GetOwner()->GetCamera();    // カメラの取得

	// World空間
	DirectX::XMFLOAT4X4 world;			                            // 行列の格納先
	DirectX::XMFLOAT4X4 view;			                            // 行列の格納先
	DirectX::XMFLOAT4X4 projection;			                        // 行列の格納先
	world = GetOwner()->GetTransform()->GetWorldMatrix();	        // ワールド行列の取得
	view = camera->GetTransposedViewMatrix();						// ビュー行列の取得
	projection = camera->GetTransposedProjectionMatrix();			// プロジェクション行列の取得

	Sprite::SetWorld(world);	                                    // ワールド行列の設定
	Sprite::SetView(view);			                                // ビュー行列の設定
	Sprite::SetProjection(projection);	                            // プロジェクション行列の設定

	VECTOR size = GetOwner()->GetTransform()->GetScale();	        // テクスチャのサイズの取得
	Sprite::SetSize(VECTOR2(size.x, size.y));	                    // サイズの設定
	Sprite::SetTexture(m_pTex);			                            // テクスチャの設定
	RenderTarget* RTV = RENDERER.GetDefaultRTV();
	RENDERER.SetRenderTargets(1, &RTV, nullptr);
	Sprite::Draw();							                        // 描画
}
