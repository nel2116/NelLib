#pragma once
// ====== インクルード ======
#include <DirectX/Texture.h>
#include <Objects/Camera/CameraBase.h>
#include <System/Scenes/Scene.h>
#include <Title/TitleUI.h>
#include <Title/TitleBackGround.h>

// ====== クラスの宣言 ======
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene() {}

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

private:
	TitleUI* m_TitleUI;
	TitleBackGround* m_TitleBackGround;
};