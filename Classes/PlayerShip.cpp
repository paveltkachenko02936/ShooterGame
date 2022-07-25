#include "PlayerShip.h"
#include "GameComponents.h"
#include "GameObjectsFactory.h"
#include "GameObjectsManager.h"
#include "Rocket.h"

using namespace std;
USING_NS_CC;

namespace
{
	const string kRocketSettingsName = "rocket";
	const string kLaunchRocketUpdate = "launchUpdate";
}

PlayerShip::PlayerShip(const GameObjectSettings* data) :
	GameObject(data)
{
	const Size& visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2& origin = Director::getInstance()->getVisibleOrigin();

	float posX = origin.x + visibleSize.height / 5;
	float posY = origin.y + visibleSize.height / 2;
	setPosition(posX, posY);

	emitHPUpdated();
}

void PlayerShip::moveBy(float dx, float dy)
{
	const auto& visibleSize = Director::getInstance()->getVisibleSize();
	const auto& size = getContentSize();

	if (dy <= size.height * 0.5f || dy >= visibleSize.height - size.height * 0.5f)
		return;

	setPosition(getPosition().x, dy);
}

void PlayerShip::startAction()
{
	auto components = GameComponents::getInstance();
	if (!components)
		return;

	auto settings = components->getSettings();
	if (!settings)
		return;

	const auto data = settings->getSettingsForObject(kRocketSettingsName);
	if (!data)
		return;

	Director::getInstance()->getScheduler()->schedule(
		[this](float) { launchRocket(); }, this, data->Cooldown, false, kLaunchRocketUpdate);
}

void PlayerShip::stopAction()
{
	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}

void PlayerShip::emitHPUpdated()
{
	auto components = GameComponents::getInstance();
	if (!components)
		return;

	if (auto stats = components->getStats())
		stats->updateUserHP(health);
}

void PlayerShip::launchRocket()
{
	auto  rocket = GameObjectsFactory::createObject(kRocketSettingsName);
	if (!rocket)
		return;

	const Vec2& parentPos = getPosition();
	const Size& parentSize = getContentSize();

	float posX = parentPos.x + parentSize.width;
	float posY = parentPos.y + parentSize.height * 0.5f;
	rocket->setPosition(posX, posY);
	rocket->startMove();
}
