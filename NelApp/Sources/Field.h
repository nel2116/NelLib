#pragma once

// ====== �C���N���[�h�� ======
#include <Objects/Object.h>
#include <vector>
#include <algorithm>
#include <System/VECTOR.h>
#include <Managers/TextureManager.h>
#include <DirectX/Shader.h>
#include <System/Model.h>

// ====== �O���錾 ======
using namespace std;

// ====== �N���X�錾 ======
class Field : public Object
{
public:	// enum
	enum mapType
	{
		Wall = 0,	// ��
		Room,		// ����
		Route,		// �ʘH
		Stairs,		// �K�i
		Chara,		// �L�����N�^�[
	};

	enum mapDir
	{
		Vertical = 0,	// �c
		Horizontal,		// ��
	};

public:
	// �R���X�g���N�^
	Field();
	// �f�X�g���N�^
	~Field();

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;


private:
	void map(int w, int h);

	// �̈�O���ǂ����̔���
	bool IsOutOfRange(int x, int y);

	// �v�f�̎擾
	int GetElement(int x, int y);

	// �v�f�̏�������
	void Set(int x, int y, int v);

	// �͈͓��̂��ׂĂ�����������
	void SetAll(int left, int top, int right, int bottom, int v);

	// ��ԕ���
	// �㉺���E�̍��W�ƕ����ԍ����擾
	void DivideArea(int left, int top, int right, int bottom, int room);

	// ���������
	// �n�_��xy���W�A�I�_��xy���W�A���� 0-> ver 1-> hor
	void DivideLine(int sx, int sy, int tx, int ty, int dir);

	// �������쐬
	void InsertDivideRoom(int left, int top, int right, int bottom);

	// �����̎擾
	// s�ȏ�t�����̗������擾
	int GetRandom(int s, int t);

	// ��Ԃ𕪊�����
	void AreaDivide();

	// ����������Ԃɏ���������������
	void CreateRoom();

	// ��������ʘH�����΂�
	// �ʘH�̓}�b�v�ɏ�������
	void CreateRoute();

	// ���@��A���S���Y��
	void DigHole(int x, int y);

	// ���@��J�n
	void DigHoleStart(int width, int height, int sx, int sy);

	// �����@�J�n
	void DivideStart(int width, int height);

	// �����_���ȕ����̈�ɊK�i��z�u����
	void SetStairs();

	// �L�����N�^�[�̔z�u
	void SetChara();

	// �}�b�v�̒[��ǂɂ���
	void SetWall();

private: // �����o�ϐ�
	int m_width;                        // ��
	int m_height;                       // ����
	int m_outOfRange;                   // �͈͊O
	vector<vector<int>> m_map;          // �}�b�v
	vector<vector<int>> m_divideArea;	// ��ԕ���(�̈�)
	vector<vector<int>> m_divideLine;	// ��ԕ���(��)
	vector<vector<int>> m_divideRoom;	// ��ԕ���(����)
	bool m_isStart;                     // �J�n�t���O
	Vector3 m_StartPos;                 // �J�n�ʒu
	Vector3 m_EndPos;                   // �I���ʒu
	Texture* m_pWall;					// �e�N�X�`��
	Texture* m_pFloor;					// �e�N�X�`��
	PixelShader* m_pPS;					// �s�N�Z���V�F�[�_�[
	VertexShader* m_pVS;				// ���_�V�F�[�_�[
	Model* m_pModel;					// ���f��
};
