#pragma once

#include <memory>
#include "Macro.h"

// �V���O���g���N���X
template <class T>
class Singleton
{
public:
	// �V���O���g���̃C���X�^���X�̎擾
	static T& GetInstance()
	{
		static typename T::singleton_pointer_type s_singleton(T::createInstance());

		return getReference(s_singleton);
	}

private:
	// �V���O���g���̃|�C���^�^
	// �X�}�[�g�|�C���^�Ȃ̂Ŏq�N���X���J������K�v�͂Ȃ�
	typedef std::unique_ptr<T> singleton_pointer_type;
	// �f�t�H���g�R���X�g���N�^�ȊO�ŃC���X�^���X���\�z�������ꍇ�AcreateInstance()���㏑������
/*
Hoge(int) { std::cout << "Hoge(int)" << std::endl; }
static Hoge *createInstance()
{
  return new Hoge(0);
}
*/
	inline static T* createInstance() { return NEW T(); }
	// �V���O���g���̎Q�Ƃ̎擾
	inline static T& getReference(const singleton_pointer_type& ptr) { return *ptr; }

protected:
	// �R���X�g���N�^
	Singleton() {}

private:
	// �R�s�[�֎~
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
};
// �g����
// �V���O���g���N���X�̌p��
// class Hoge : public Singleton<Hoge>
// {
// public:
// 	// �f�X�g���N�^
// 	~Hoge() {}
// private:
// 	// �R���X�g���N�^
// 	friend Singleton<Hoge>;
// 	Hoge() {}
// };
// 
// ������Ȃ��Ƃ��낪��������ȉ�URL���Q�Ƃ��Ă�������
// https://cflat-inc.hatenablog.com/entry/2014/03/04/214608