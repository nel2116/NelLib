#include "EnemyFactory.h"
#include <Managers/ObjectsManager.h>
#include "Slime.h"

Enemy* EnemyFactory::CreateEnemy(int type)
{
	switch (type)
	{
	case 0:	return CreateSlime();	    // スライムの生成
	case 1:	return CreateGoblin();	    // ゴブリンの生成
	case 2:	return CreateBat();		    // コウモリの生成
	case 3:	return CreateSpider();	    // クモの生成
	case 4:	return CreateSkeleton();	// スケルトンの生成
	case 5:	return CreateDragon();	    // ドラゴンの生成
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
	// ゴブリン
	//Goblin* pGoblin = OBJECTS_MANAGER.AddObject<Goblin>();
	//pGoblin->Init();
	//return pGoblin;
	return nullptr;
}

Enemy* EnemyFactory::CreateBat()
{
	// コウモリ
	//Bat* pBat = OBJECTS_MANAGER.AddObject<Bat>();
	//pBat->Init();
	//return pBat;
	return nullptr;
}

Enemy* EnemyFactory::CreateSpider()
{
	// クモ
	//Spider* pSpider = OBJECTS_MANAGER.AddObject<Spider>();
	//pSpider->Init();
	//return pSpider;
	return nullptr;
}

Enemy* EnemyFactory::CreateSkeleton()
{
	// スケルトン
	//Skeleton* pSkeleton = OBJECTS_MANAGER.AddObject<Skeleton>();
	//pSkeleton->Init();
	//return pSkeleton;
	return nullptr;
}

Enemy* EnemyFactory::CreateDragon()
{
	// ドラゴン
	//Dragon* pDragon = OBJECTS_MANAGER.AddObject<Dragon>();
	//pDragon->Init();
	//return pDragon;
	return nullptr;
}
