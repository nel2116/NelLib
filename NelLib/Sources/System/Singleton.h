#pragma once

#include <memory>
#include "Macro.h"

// シングルトンクラス
template <class T>
class Singleton
{
public:
	// シングルトンのインスタンスの取得
	static T& GetInstance()
	{
		static typename T::singleton_pointer_type s_singleton(T::createInstance());

		return getReference(s_singleton);
	}

private:
	// シングルトンのポインタ型
	// スマートポインタなので子クラスを開放する必要はない
	typedef std::unique_ptr<T> singleton_pointer_type;
	// デフォルトコンストラクタ以外でインスタンスを構築したい場合、createInstance()を上書きする
/*
Hoge(int) { std::cout << "Hoge(int)" << std::endl; }
static Hoge *createInstance()
{
  return new Hoge(0);
}
*/
	inline static T* createInstance() { return NEW T(); }
	// シングルトンの参照の取得
	inline static T& getReference(const singleton_pointer_type& ptr) { return *ptr; }

protected:
	// コンストラクタ
	Singleton() {}

private:
	// コピー禁止
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
};
// 使い方
// シングルトンクラスの継承
// class Hoge : public Singleton<Hoge>
// {
// public:
// 	// デストラクタ
// 	~Hoge() {}
// private:
// 	// コンストラクタ
// 	friend Singleton<Hoge>;
// 	Hoge() {}
// };
// 
// 分からないところがあったら以下URLを参照してください
// https://cflat-inc.hatenablog.com/entry/2014/03/04/214608