// ====== �C���N���[�h�� ======
#include<crtdbg.h>
#include <DirectX/Renderer.h>
#include <DirectX/Sprite.h>
#include <NelLib.h>
#include <Managers/ObjectsManager.h>
#include <Managers/SceneManager.h>
#include <Managers/TimeManger.h>
#include <Managers/CameraManager.h>
#include <Managers/TextureManager.h>
#include <Managers/ModelManager.h>

// ====== �v���g�^�C�v�錾 ======
void Init();
void Uninit();
void Input();
void Update();
void Draw();

void window(const char* appName, int width, int height)
{
	// �e������
	createWindow(appName, width, height);
	RENDERER.Init(width, height, false);
	Geometory::Init();					// �W�I���g��������
	Sprite::Init();						// �X�v���C�g������
	InitInput();						// ���͏�����
	// �}�l�[�W��������
	MODEL_MANAGER.Init();				// ���f���}�l�[�W��������
	OBJECTS_MANAGER.Init();				// �I�u�W�F�N�g�}�l�[�W��������
	SCENE_MANAGER.Init();				// �V�[���}�l�[�W��������
	TEXTURE_MANAGER.Init();				// �e�N�X�`���}�l�[�W��������
	TIME_MANAGER.Init();				// �^�C���}�l�[�W��������
	CAMERA_MANAGER.Init();				// �J�����}�l�[�W��������

	// �W�I���g���p�J����������
	DirectX::XMFLOAT4X4 mat[2];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		)));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(60.0f), (float)width / height, 0.1f, 100.0f)
	));
	Geometory::SetView(mat[0]);
	Geometory::SetProjection(mat[1]);
}

void DrawGrid()
{
	// �O���b�h
	DirectX::XMFLOAT4 lineColor(0.5f, 0.5f, 0.5f, 1.0f);
	float size = DEBUG_GRID_NUM * DEBUG_GRID_MARGIN;
	for (int i = 1; i <= DEBUG_GRID_NUM; ++i)
	{
		float grid = i * DEBUG_GRID_MARGIN;
		DirectX::XMFLOAT3 pos[2] = {
			DirectX::XMFLOAT3(grid, 0.0f, size),
			DirectX::XMFLOAT3(grid, 0.0f,-size),
		};
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = pos[1].x = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = size;
		pos[1].x = -size;
		pos[0].z = pos[1].z = grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].z = pos[1].z = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
	}
	// ��
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(size, 0, 0), DirectX::XMFLOAT4(1, 0, 0, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, size, 0), DirectX::XMFLOAT4(0, 1, 0, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, size), DirectX::XMFLOAT4(0, 0, 1, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(-size, 0, 0), DirectX::XMFLOAT4(0, 0, 0, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, -size), DirectX::XMFLOAT4(0, 0, 0, 1));

	Geometory::DrawLines();
}

void gmain()
{
	Init();
	while (!quit())
	{
		// �^�C���}�l�[�W���X�V
		TIME_MANAGER.Update();
		// ���͏��̍X�V
		UpdateInput();
		// �E�B���h�E������ꂽ��I��
		if (escKeyPressed()) { closeWindow(); }

		if (TIME_MANAGER.GetDeltaTimeSecond() >= 1.0f / 60)
		{
			// �ȉ��ɃQ�[���̏���������
			// ===== ���͏��� =====
			Input();
			// ===== �X�V���� =====
			SCENE_MANAGER.Update();
			Update();
			// ===== �`�揈�� =====

			// ===== �`�揈�� =====
			RENDERER.Begin();	// �`��J�n

			Draw();

			RENDERER.End();		// �`��I��

			// �ŏI���s���Ԃ̍X�V
			TIME_MANAGER.UpdateLastTime();
		}
	}
	Uninit();
}

int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ INT)
{
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �Q�[���̃��C�����[�v
	gmain();

	// �V�X�e���̏I������
	UninitInput();
	Sprite::Uninit();
	Geometory::Uninit();
	RENDERER.Release();
	return 0;
}