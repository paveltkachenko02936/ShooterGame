#pragma once
#include <vector>
#include <memory>
#include <map>
#include "GameSettings.h"

class SpawnTimer final
{
public:
	explicit SpawnTimer(const TimerSettings* settings);

	void update(float delta);
	int getRemainTime() const { return time; }
	float getSpawnInterval() const { return spawnInterval; }

private:
	int time = 0;
	float spawnInterval = 0.0f;
};

class EnemyEmitter final
{
public:
	void start();

private:
	void update(float delta);
	void spawn(const string& enemyType);
	void checkAllObjectsForSpawn();
	bool rollChance(float value);
	void scheduleSpawn();

private:
	int currentTimerIndex = 0;
	std::vector<std::unique_ptr<SpawnTimer>> timers;
	std::map<string, float> chances;
};