#include "EnemyEmitter.h"
#include "GameComponents.h"
#include "GameSettings.h"
#include <vector>
#include "cocos2d.h"
#include "GameObject.h"
#include "GameObjectsFactory.h"

using namespace std;
USING_NS_CC;

namespace
{
	const string kSpawnScheduler = "spawnScheduler";
}

void EnemyEmitter::start()
{
	auto components = GameComponents::getInstance();
	if (!components)
		return;

	auto settings = components->getSettings();
	if (!settings)
		return;

	const auto& timersSettings = settings->getTimersSettings();

	for (const auto timerSetting : timersSettings)
	{
		auto timer = make_unique<SpawnTimer>(timerSetting);
		timers.push_back(std::move(timer));
	}

	const auto& enemiesSettings = settings->getEnemiesSettings();
	for (const auto enemySetting : enemiesSettings)
	{
		chances[enemySetting->Type] = enemySetting->SpawnChance;
	}

	Director::getInstance()->getScheduler()->schedule(
		[this](float delta) {update(delta); }, this, 0.0, false, "enemyEmitterUpdate");

	scheduleSpawn();
}

void EnemyEmitter::update(float delta)
{
	if (timers[currentTimerIndex]->getRemainTime() <= 0 && currentTimerIndex != timers.size() - 1)
	{
		currentTimerIndex++;
		scheduleSpawn();
	}

	timers[currentTimerIndex]->update(delta);
}

void EnemyEmitter::spawn(const string& enemyType)
{
	auto enemy = GameObjectsFactory::createObject(enemyType);
	enemy->startMove();
}

void EnemyEmitter::checkAllObjectsForSpawn()
{
	for (auto& chancePair : chances)
	{
		if (rollChance(chancePair.second))
			spawn(chancePair.first);
	}
}

bool EnemyEmitter::rollChance(float value)
{
	const float random = (float)rand() / RAND_MAX;
	if (random >= 0.0f && random <= value)
		return true;

	return false;
}

void EnemyEmitter::scheduleSpawn()
{
	auto scheduler = Director::getInstance()->getScheduler();
	if (!scheduler)
		return;

	const float interval = timers[currentTimerIndex]->getSpawnInterval();

	scheduler->unschedule(kSpawnScheduler, this);
	scheduler->schedule([this](float delta) {checkAllObjectsForSpawn(); }, this, interval, false, kSpawnScheduler);
}

SpawnTimer::SpawnTimer(const TimerSettings* settings)
{
	if (!settings)
		return;

	time = settings->Time * 100;
	spawnInterval = settings->SpawnInterval;
}

void SpawnTimer::update(float delta)
{
	if (time > 0)
		time -= delta;
}
