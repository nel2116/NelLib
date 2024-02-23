#include "Scene.h"

void Scene::ShowName()
{
	const char* name = m_name.c_str();
	char arry[256];
	strcpy_s(arry, name);
	MessageBox(nullptr, arry, arry, MB_OK);
}
