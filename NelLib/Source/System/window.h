#pragma once
// ====== �C���N���[�h�� ======
#include"common.h"

// ====== �O���[�o���ϐ� ======
extern int ClientWidth;			// �E�B���h�E�̕�
extern int ClientHeight;		// �E�B���h�E�̍���
extern unsigned ActiveWindow;	// �A�N�e�B�u�E�B���h�E�̃n���h��
extern int MouseDelta;			// �}�E�X�̈ړ���
extern bool Windowed;			// �E�B���h�E���[�h���ǂ���
extern float DeltaTime;			// �f���^�^�C��

// ====== �v���g�^�C�v�錾 ======
/// <summary>
/// �E�B���h�E�v���V�[�W���[
/// </summary>
bool quit();
bool escKeyPressed();
/// <summary>
/// �E�B���h�E�����֐�
/// </summary>
/// <remarks>���̊֐����ĂԂƁA�E�B���h�E������</remarks>
void closeWindow();
/// <summary>
/// �E�B���h�E���쐬����֐�
/// </summary>
/// <param name="appName">�E�B���h�E�̃^�C�g��</param>
/// <param name="windowWidth">�E�B���h�E�̕�</param>
/// <param name="windowHeight">�E�B���h�E�̍���</param>
/// <remarks>���̊֐����ĂԂƁA�E�B���h�E���쐬�����</remarks>
/// <remarks>���̊֐��́A�Q�[���̏����������̒��ŌĂ�</remarks>
void createWindow(const char* appName, int windowWidth, int windowHeight);

#define delta DeltaTime			// �f���^�^�C���̕ʖ�
/// <summary>
/// �f���^�^�C��������������֐�
/// </summary>
/// <remarks>���̊֐����ĂԂƁA�f���^�^�C���������������</remarks>
/// <remarks>���̊֐��́A�Q�[���̏����������̒��ŌĂ�</remarks>
/// <remarks>���̊֐��́AcreateWindow()�̌�ɌĂ�</remarks>
void initDeltaTime();
/// <summary>
/// �f���^�^�C�����X�V����֐�
/// </summary>
/// <remarks>���̊֐����ĂԂƁA�f���^�^�C�����X�V�����</remarks>
/// <remarks>���̊֐��́A�Q�[���̍X�V�����̒��ŌĂ�</remarks>
void setDeltaTime();
/// <summary>
/// �f���^�^�C�����擾����֐�
/// </summary>
/// <returns>�f���^�^�C��</returns>
/// <remarks>���̊֐��́A�Q�[���̍X�V�����̒��ŌĂ�</remarks>
/// <remarks>���̊֐��́AsetDeltaTime()�̌�ɌĂ�</remarks>
unsigned getTime();
