#ifndef ___TEST_OBJECT_H___
#define ___TEST_OBJECT_H___
#include <System/Model.h>

// �N���X��`
class TestObject
{
public:
	// �R���X�g���N�^
	TestObject();

	// �f�X�g���N�^
	~TestObject();

	// �����o�֐�
	// ������
	void Init();
	void Update();
	void Draw();
	void Uninit();

private:
// �����o�ϐ�
	Model* m_pModel;
};

#endif // !___TEST_OBJECT_H___
