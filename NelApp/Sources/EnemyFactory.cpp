#include "EnemyFactory.h"
#include <Managers/ObjectsManager.h>
#include "Slime.h"

Enemy* EnemyFactory::CreateEnemy(int type)
{
	switch (type)
	{
	case 0:	return CreateSlime();	    // �X���C���̐���
	case 1:	return CreateGoblin();	    // �S�u�����̐���
	case 2:	return CreateBat();		    // �R�E�����̐���
	case 3:	return CreateSpider();	    // �N���̐���
	case 4:	return CreateSkeleton();	// �X�P���g���̐���
	case 5:	return CreateDragon();	    // �h���S���̐���
	default: return nullptr;
	}
}

Enemy* EnemyFactory::CreateSlime()
{
	Slime* pSlime = OBJECTS_MANAGER.AddObjects<Slime>();
	pSlime->Init();
	return pSlime;
}

Enemy* EnemyFactory::CreateGoblin()
{
	// �S�u����
	//Goblin* pGoblin = OBJECTS_MANAGER.AddObject<Goblin>();
	//pGoblin->Init();
	//return pGoblin;
	return nullptr;
}

Enemy* EnemyFactory::CreateBat()
{
	// �R�E����
	//Bat* pBat = OBJECTS_MANAGER.AddObject<Bat>();
	//pBat->Init();
	//return pBat;
	return nullptr;
}

Enemy* EnemyFactory::CreateSpider()
{
	// �N��
	//Spider* pSpider = OBJECTS_MANAGER.AddObject<Spider>();
	//pSpider->Init();
	//return pSpider;
	return nullptr;
}

Enemy* EnemyFactory::CreateSkeleton()
{
	// �X�P���g��
	//Skeleton* pSkeleton = OBJECTS_MANAGER.AddObject<Skeleton>();
	//pSkeleton->Init();
	//return pSkeleton;
	return nullptr;
}

Enemy* EnemyFactory::CreateDragon()
{
	// �h���S��
	//Dragon* pDragon = OBJECTS_MANAGER.AddObject<Dragon>();
	//pDragon->Init();
	//return pDragon;
	return nullptr;
}
