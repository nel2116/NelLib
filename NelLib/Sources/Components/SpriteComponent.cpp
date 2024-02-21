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
	m_spriteInfo.texture = TEXTURE_MANAGER.GetTexture(TextureManager::TEX_DEFAULT);   // テクスチャの取得
	m_pCamera = CAMERA_MANAGER.GetCamera(CameraManager::E_CAM_UI);		// カメラの設定
}

void SpriteComponent::Uninit()
{
}

void SpriteComponent::Update()
{
}

void SpriteComponent::Draw()
{
	// カメラがない場合は描画しない
	if (!m_pCamera) { return; }

	// // World空間
	// DirectX::XMMATRIX mat[3] = {};			// 行列の宣言
	// mat[0] = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	// mat[0] = DirectX::XMMatrixTranspose(mat[0]);	// シェーダに渡す前に実行する処理
	// DirectX::XMFLOAT4X4 fmat;				// 行列の格納先
	// DirectX::XMStoreFloat4x4(&fmat, mat[0]);	// matをfmatに格納する処理
	// Sprite::SetWorld(fmat);					// 行列をシェーダに渡す処理
	// 
	// // View空間
	// mat[1] = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f), DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	// mat[1] = DirectX::XMMatrixTranspose(mat[1]);
	// DirectX::XMStoreFloat4x4(&fmat, mat[1]);
	// Sprite::SetView(fmat);
	// 
	// // Projection空間
	// mat[2] = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), 1280.0f / 720.0f, 0.3f, 100.0f);
	// mat[2] = DirectX::XMMatrixTranspose(mat[2]);
	// DirectX::XMStoreFloat4x4(&fmat, mat[2]);
	// Sprite::SetProjection(fmat);
	// 
	// Sprite::SetSize(VECTOR2(0.5f, 0.5f));	// サイズの設定
	// Sprite::SetTexture(nullptr);			// テクスチャの設定
	// Sprite::Draw();							// 描画




	// World空間
	DirectX::XMFLOAT4X4 world;								// 行列の格納先
	DirectX::XMFLOAT4X4 view;								// 行列の格納先
	DirectX::XMFLOAT4X4 projection;							// 行列の格納先
	DirectX::XMMATRIX vie;									// 行列の宣言
	DirectX::XMMATRIX proj;									// 行列の宣言

	world = GetOwner()->GetTransform()->GetWorldMatrix();	// ワールド行列の取得


	view = m_pCamera->GetViewMatrix();						// ビュー行列の取得

	projection = m_pCamera->GetProjectionMatrix();			// プロジェクション行列の取得
	// proj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), 1280.0f / 720.0f, 0.3f, 100.0f);
	// proj = DirectX::XMMatrixTranspose(proj);				// シェーダに渡す前に実行する処理
	// DirectX::XMStoreFloat4x4(&projection, proj);			// projをprojectionに格納する処理

	Sprite::SetWorld(world);								// ワールド行列の設定
	Sprite::SetView(view);									// ビュー行列の設定
	Sprite::SetProjection(projection);						// プロジェクション行列の設定

	Sprite::SetColor(m_spriteInfo.color);					// 色の設定

	Sprite::SetSize(m_spriteInfo.size);						// サイズの設定
	Sprite::SetOffset(Vector2::zero());						// オフセットの設定

	Sprite::SetUVPos(m_spriteInfo.uvOffset);				// UV座標の設定
	Sprite::SetUVScale(m_spriteInfo.uvScale);				// UVサイズの設定

	Sprite::SetTexture(m_spriteInfo.texture);				// テクスチャの設定
	RenderTarget* RTV = RENDERER.GetDefaultRTV();
	RENDERER.SetRenderTargets(1, &RTV, nullptr);
	Sprite::Draw();											// 描画
}

void SpriteComponent::SetSizeToTexture()
{
	if (m_spriteInfo.texture)
	{
		// テクスチャのサイズを取得
		m_spriteInfo.size.x = (float)m_spriteInfo.texture->GetWidth();
		m_spriteInfo.size.y = (float)m_spriteInfo.texture->GetHeight();

		// サイズの設定
		m_spriteInfo.size *= m_spriteInfo.uvScale;
	}
}

void SpriteComponent::SetSplit(Vector2 split)
{
	// --- 分割設定
	m_spriteInfo.uvScale.x = 1.0f / split.x;
	m_spriteInfo.uvScale.y = 1.0f / split.y;

	m_spriteInfo.size.x *= m_spriteInfo.uvScale.x;
	m_spriteInfo.size.y *= m_spriteInfo.uvScale.y;

	m_spriteInfo.splitX = static_cast<int>(split.x);
	m_spriteInfo.splitY = static_cast<int>(split.y);
}

void SpriteComponent::SetIndex(int index)
{
	// --- インデックス設定
	m_spriteInfo.uvOffset.x = (index % m_spriteInfo.splitX) * m_spriteInfo.uvScale.x;
	m_spriteInfo.uvOffset.y = (index / m_spriteInfo.splitX) * m_spriteInfo.uvScale.y;
}
