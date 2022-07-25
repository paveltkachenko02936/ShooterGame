#include "Enemy.h"
#include "GameSettings.h"
#include "GameComponents.h"

using namespace std;
USING_NS_CC;

Enemy::Enemy(const GameObjectSettings* data) :GameObject(data)
{
	const Size& visibleSize = Director::getInstance()->getVisibleSize();
	const Size& contentSize = getContentSize();

	float posX = visibleSize.width + contentSize.width;
	float posY = rand() % static_cast<int>(visibleSize.height - contentSize.height);

	setPosition(posX, posY);

	scorePoints = data->Health;
	ignoreUserWeapon = data->IgnoreUserWeapon;
}

void Enemy::startMove()
{
	const Size& sceneSize = Director::getInstance()->getVisibleSize();
	const Size& contentSize = getContentSize();

	const float distance = sceneSize.width + contentSize.width;

	auto action = MoveBy::create(std::abs(distance) / speed, Point(-distance, 0));
	auto callback = CallFunc::create(
		[this]()
		{
			removeFromManager();
		});
	auto sequence = Sequence::create(action, callback, NULL);

	this->runAction(sequence);
}

void Enemy::onDestroyed()
{
	auto components = GameComponents::getInstance();
	if (!components)
		return;

	if (auto stats = components->getStats())
		stats->updateScore(scorePoints);
}
