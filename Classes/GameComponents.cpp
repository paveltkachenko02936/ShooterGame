#include "GameComponents.h"

using namespace std;

GameComponents* GameComponents::getInstance()
{
	static GameComponents* instance = new GameComponents();
	return instance;
}

void GameComponents::createComponents()
{
	gameSettings = std::make_unique<GameSettings>();
	gameSettings->Load();

	stats = std::make_unique<Stats>();

	objectsManager = std::make_unique<GameObjectsManager>();

	enemyEmitter = std::make_unique<EnemyEmitter>();
	enemyEmitter->start();
}