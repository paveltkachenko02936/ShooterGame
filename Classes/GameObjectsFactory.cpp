#include "GameObjectsFactory.h"
#include "GameSettings.h"
#include "PlayerShip.h"
#include "GameComponents.h"
#include "GameObjectsManager.h"
#include "Enemy.h"
#include "Rocket.h"

using namespace std;

GameObject* GameObjectsFactory::createObject(const string& type)
{
	auto components = GameComponents::getInstance();
	if (!components)
		return nullptr;

	auto settings = components->getSettings();
	if (!settings)
		return nullptr;

	const auto data = settings->getSettingsForObject(type);
	if (!data)
		return nullptr;

	auto objectsManager = components->getGameObjects();
	if (!objectsManager)
		return nullptr;

	GameObject* obj = nullptr;
	if (type == "player")
	{
		obj = new PlayerShip(data);
		objectsManager->assignPlayer(obj);
	}
	else if (data->IsEnemy)
	{
		obj = new Enemy(data);
		objectsManager->addEnemy(obj);
	}
	else if (type == "rocket")
	{
		obj = new Rocket(data);
		objectsManager->addRocket(obj);
	}

	return obj;
}
