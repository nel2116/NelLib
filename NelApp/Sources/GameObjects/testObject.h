#ifndef ___TEST_OBJECT_H___
#define ___TEST_OBJECT_H___
#include <System/Model.h>
#include <DirectX/Shader.h>
#include <Objects/Object.h>

// �N���X��`
class TestObject : public Object
{
public:
	// �R���X�g���N�^
	TestObject();

	// �f�X�g���N�^
	~TestObject();

	// �����o�֐�
	// ������
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

private:
	// �����o�ϐ�
	Model* m_pModel;
	VertexShader* m_pVS;
};

#endif // !___TEST_OBJECT_H___
