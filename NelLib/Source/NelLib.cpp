
#include<crtdbg.h>
#include "../Source/DirectX/Renderer.h"
#include "NelLib.h"
void gmain();

void window(const char* appName, int width, int height)
{
    createWindow(appName,width,height);
    RENDERER.Init(width,height,false);
}

int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ INT)
{
    // ���������[�N���o
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    // �Q�[���̃��C�����[�v
    gmain();
    // �C���X�^���X�̍폜
    RENDERER.Release();
    RENDERER.DestroyInstance();
	return 0;
}