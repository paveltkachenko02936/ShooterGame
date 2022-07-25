#pragma once

#include <map>
#include <vector>
#include <string>
#include "cocos-ext.h"

using namespace std;

struct GameObjectSettings
{
	string Type = "";
	int Speed = 0;
	int Health = 0;
	int Power = 0;
	float Cooldown = 0.0f;
	float SpawnChance = 0.0f;
	string ImagePath = "";
	bool IsEnemy = false;
	bool IgnoreUserWeapon = false;
};

struct TimerSettings
{
	int Time = -1;
	float SpawnInterval = 0.0f;
};

class GameSettings final
{
public:
	~GameSettings();

	void Load();

	const GameObjectSettings* getSettingsForObject(const string& type) const;
	const std::vector<TimerSettings*>& getTimersSettings() const { return timersSettings; }
	const std::vector<GameObjectSettings*>& getEnemiesSettings() const { return enemiesSettings; }

private:
	GameObjectSettings* createObjectSettings(const rapidjson::Value& json);
	TimerSettings* createTimerSettings(const rapidjson::Value& json);

private:
	std::map<string, GameObjectSettings*> objectsSettings;
	std::vector<TimerSettings*> timersSettings;
	std::vector<GameObjectSettings*> enemiesSettings;
};