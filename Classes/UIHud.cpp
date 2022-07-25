#include "UIHud.h"
#include "2d/CCLabel.h"
#include "GameComponents.h"
#include "Stats.h"
#include "2d/CCScene.h"

USING_NS_CC;
using namespace std;

UIHud::UIHud(cocos2d::Scene* scene)
{
	auto components = GameComponents::getInstance();
	if (!components)
		return;

	stats = components->getStats();
	if (!stats)
		return;

	stats->addListener(this);

	hpLabel = Label::createWithSystemFont("H:" + std::to_string(stats->getUserHP()), "Arial", 20);
	hpLabel->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	hpLabel->setDimensions(100, 30);
	hpLabel->setPosition(10, 0);
	scene->addChild(hpLabel);

	scoreLabel = Label::createWithSystemFont("P:" + std::to_string(stats->getScore()), "Arial", 20);
	scoreLabel->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	scoreLabel->setDimensions(100, 30);
	scoreLabel->setPosition(100, 0);
	scene->addChild(scoreLabel);
}

UIHud::~UIHud()
{
	if (stats)
		stats->removeListener(this);
}

void UIHud::onStatsUpdated(EStatsType type)
{
	if (!stats)
		return;

	if (hpLabel && type == EStatsType::UserHP)
	{
		std::string str = "H:" + to_string(stats->getUserHP());
		hpLabel->setString(str);
	}

	if (scoreLabel && type == EStatsType::Score)
	{
		std::string str = "P:" + to_string(stats->getScore());
		scoreLabel->setString(str);
	}
}

