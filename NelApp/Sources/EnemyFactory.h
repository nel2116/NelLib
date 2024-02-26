#pragma once
// ====== �C���N���[�h�� ======
#include "Enemy.h"

// ====== �N���X�̐錾 ======
class EnemyFactory
{
public:

	static Enemy* CreateEnemy(int type);
private:
	static Enemy* CreateSlime();
	static Enemy* CreateGoblin();
	static Enemy* CreateBat();
	static Enemy* CreateSpider();
	static Enemy* CreateSkeleton();
	static Enemy* CreateDragon();
};