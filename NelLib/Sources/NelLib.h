#pragma once
// ====== �C���N���[�h�� ======
#include <System/window.h>
#include <System/Geometory.h>
#include <System/Input.h>

// ====== �萔�E�}�N����` ======
// �O���b�h�T�C�Y
#define DEBUG_GRID_NUM (10) // �O���b�h���S����[�܂ł̐��̐�
#define DEBUG_GRID_MARGIN (1.0f) // �O���b�h�z�u��(���[�g�����Z)

void window(const char* appName, int width, int height);
void DrawGrid();