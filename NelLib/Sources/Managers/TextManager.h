#pragma once
// ====== �C���N���[�h�� ======
#include <string>
#include <vector>
#include <System/Singleton.h>
#include <System/VECTOR.h>
#include <System/DirectWriteCustomFont.h>

// ====== �N���X�錾 ======
class TextManager : public Singleton<TextManager>
{
public:
	struct Text
	{
		std::string string;
		Vector2 pos;
		int drawFrame;
	};

public:
	// �f�X�g���N�^
	~TextManager() { Uninit(); }

	// ������
	void Init();

	// �I��
	void Uninit();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �e�L�X�g�̒ǉ�
	void AddText(std::string string, Vector2 pos, int frame);

private:
	// �e�L�X�g�̃��X�g
	std::vector<Text> m_TextList;

	DirectWriteCustomFont* m_pWrite;
	FontData m_FontData;
	int drawNum;

	Vector2 m_pos;

private: //	�V���O���g���֘A
	friend class Singleton<TextManager>;
	TextManager() : drawNum(0), m_pWrite(nullptr), m_FontData() {}
};
// �C���X�^���X�擾
#define TEXT_MANAGER TextManager::GetInstance()