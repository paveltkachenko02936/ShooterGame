#include "GameObject.h"
#include "GameSettings.h"
#include "GameComponents.h"

USING_NS_CC;

GameObject::GameObject(const GameObjectSettings* data)
{
	speed = data->Speed;
	health = data->Health;
	power = data->Power;

	if (!data->ImagePath.empty())
	{
		auto image = Sprite::create(data->ImagePath + ".png");
		addChild(image);
		setContentSize(image->getContentSize());
	}
}

void GameObject::hit(int damage)
{
	health -= damage;

	if (health <= 0)
		health = 0;

	emitHPUpdated();

	if (health == 0)
	{
		onDestroyed();
		removeFromManager();
	}
}

void GameObject::removeFromManager()
{
	auto components = GameComponents::getInstance();
	if (!components)
		return;

	auto objectsManager = components->getGameObjects();
	if (!objectsManager)
		return;

	objectsManager->removeObject(this);
}

