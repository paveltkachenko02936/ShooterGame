#include "GameObjectsManager.h"
#include "cocos2d.h"
#include "GameObject.h"
#include <algorithm>
#include "Enemy.h"

using namespace std;
USING_NS_CC;

namespace
{
	const string kCheckCollisions = "checkCollisionsUpdate";
}

GameObjectsManager::GameObjectsManager()
{
	Director::getInstance()->getScheduler()->schedule(
		[this](float delta) {checkCollisions(); }, this, 0.0, false, kCheckCollisions);
}

GameObjectsManager::~GameObjectsManager()
{
}

void GameObjectsManager::addEnemy(GameObject* obj)
{
	if (!obj)
		return;

	enemies.push_back(obj);
	Director::getInstance()->getRunningScene()->addChild(obj);
}

void GameObjectsManager::addRocket(GameObject* obj)
{
	if (!obj)
		return;

	rockets.push_back(obj);
	Director::getInstance()->getRunningScene()->addChild(obj);
}

void GameObjectsManager::removeObject(GameObject* obj)
{
	if (!obj)
		return;

	auto it = std::remove(rockets.begin(), rockets.end(), obj);
	if (it != rockets.end())
		rockets.erase(it);

	it = std::remove(enemies.begin(), enemies.end(), obj);
	if (it != enemies.end())
		enemies.erase(it);

	if (obj == player)
	{
		player = nullptr;
	}

	obj->removeFromParent();
	delete obj;
}

void GameObjectsManager::checkCollisions()
{
	if (!player)
		return;

	for (auto enemy : enemies)
	{
		if (checkCollision(player, enemy))
		{
			player->hit(enemy->getPower());
			removeObject(enemy);
		}
	}

	for (auto enemy : enemies)
	{
		if (checkIgnoreWeapon(enemy))
			continue;

		for (auto rocket : rockets)
		{
			if (checkCollision(rocket, enemy))
			{
				enemy->hit(rocket->getPower());
				removeObject(rocket);

				return;
			}
		}
	}
}

bool GameObjectsManager::checkCollision(const GameObject* first, const GameObject* second) const
{
	if (!first || !second)
		return false;

	const Rect& rect1 = first->getBoundingBox();
	const Rect& rect2 = second->getBoundingBox();

	return rect1.intersectsRect(rect2);
}

bool GameObjectsManager::checkIgnoreWeapon(GameObject* obj)
{
	if (auto enemy = dynamic_cast<Enemy*>(obj))
		return enemy->isIgnoreWeapon();

	return false;
}
