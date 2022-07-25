#include "Rocket.h"
#include "PlayerShip.h"

USING_NS_CC;

Rocket::Rocket(const GameObjectSettings* data) :GameObject(data)
{
}

void Rocket::startMove()
{
	const Size& sceneSize = Director::getInstance()->getVisibleSize();
	const float distance = sceneSize.width - getPosition().x;

	auto action = MoveBy::create(std::abs(distance) / speed, Point(distance, 0));
	auto callback = CallFunc::create(
		[this]()
		{
			removeFromManager();
		});
	auto sequence = Sequence::create(action, callback, NULL);

	this->runAction(sequence);
}
