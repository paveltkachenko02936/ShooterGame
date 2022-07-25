#pragma once

#include "GameSettings.h"
#include "EnemyEmitter.h"
#include "Stats.h"
#include "GameObjectsManager.h"

using namespace std;

class GameComponents final
{
public:
	static GameComponents* getInstance();
	void createComponents();

	GameSettings* getSettings() const { return gameSettings.get(); }
	EnemyEmitter* getEnemyEmitter() const { return enemyEmitter.get(); }
	GameObjectsManager* getGameObjects() const { return objectsManager.get(); }
	Stats* getStats() const { return stats.get(); }

private:
	std::unique_ptr<GameSettings> gameSettings;
	std::unique_ptr<EnemyEmitter> enemyEmitter;
	std::unique_ptr<GameObjectsManager> objectsManager;
	std::unique_ptr<Stats> stats;
};