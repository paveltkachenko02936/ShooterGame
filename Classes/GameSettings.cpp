
#include "GameSettings.h"
#include <string>
#include <vector>
#include "cocos-ext.h"
#include "json/reader.h"
#include "json/writer.h"
#include "json/document.h"
#include "json/stringbuffer.h"

using namespace std;
using namespace rapidjson;
USING_NS_CC;

namespace
{
	const string fileName = "Settings.json";
}

GameSettings::~GameSettings()
{
	for (const auto& setting : objectsSettings)
		delete setting.second;

	for (auto timerSettings : timersSettings)
		delete timerSettings;

	objectsSettings.clear();
	timersSettings.clear();
	enemiesSettings.clear();
}

void GameSettings::Load()
{
	rapidjson::Document document;
	const string& content = FileUtils::getInstance()->getStringFromFile(fileName.c_str());
	log("file content: %s", content.c_str());
	document.Parse<0>(content.c_str());

	if (document.HasMember("objects"))
	{
		const rapidjson::Value& jObjects = document["objects"];
		if (jObjects.IsArray())
		{
			const auto& objects = jObjects.GetArray();
			for (const auto& jObjSetting : objects)
			{
				auto settings = createObjectSettings(jObjSetting);
				if (!settings)
					continue;

				objectsSettings[settings->Type] = settings;
				if (settings->IsEnemy)
					enemiesSettings.push_back(settings);
			}
		}
	}

	if (document.HasMember("timers"))
	{
		const rapidjson::Value& jTimers = document["timers"];
		if (jTimers.IsArray())
		{
			const auto& timers = jTimers.GetArray();
			for (const auto& jObjTimer : timers)
			{
				auto settings = createTimerSettings(jObjTimer);
				if (!settings)
					continue;

				timersSettings.push_back(settings);
			}
		}
	}
}

const GameObjectSettings* GameSettings::getSettingsForObject(const string& type) const
{
	auto found = objectsSettings.find(type);
	if (found == objectsSettings.end())
		return nullptr;

	return found->second;
}

GameObjectSettings* GameSettings::createObjectSettings(const rapidjson::Value& json)
{
	auto settings = new GameObjectSettings();

	if (json.HasMember("type"))
		settings->Type = json["type"].GetString();

	if (json.HasMember("speed"))
		settings->Speed = json["speed"].GetInt();

	if (json.HasMember("power"))
		settings->Power = json["power"].GetInt();

	if (json.HasMember("health"))
		settings->Health = json["health"].GetInt();

	if (json.HasMember("image"))
		settings->ImagePath = json["image"].GetString();

	if (json.HasMember("cooldown"))
		settings->Cooldown = json["cooldown"].GetFloat();

	if (json.HasMember("spawnChance"))
		settings->SpawnChance = json["spawnChance"].GetFloat();

	if (json.HasMember("isEnemy"))
		settings->IsEnemy = json["isEnemy"].GetBool();

	if (json.HasMember("ignoreUserWeapon"))
		settings->IgnoreUserWeapon = json["ignoreUserWeapon"].GetBool();

	return settings;
}

TimerSettings* GameSettings::createTimerSettings(const rapidjson::Value& json)
{
	auto settings = new TimerSettings();

	if (json.HasMember("time"))
		settings->Time = json["time"].GetInt();

	if (json.HasMember("spawnInterval"))
		settings->SpawnInterval = json["spawnInterval"].GetFloat();

	return settings;
}
