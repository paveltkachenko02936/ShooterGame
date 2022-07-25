#pragma once
#include "Stats.h"
#include "2d/CCScene.h"
#include "2d/CCLabel.h"

USING_NS_CC;

class UIHud : private StatsListener
{
public:
	explicit UIHud(cocos2d::Scene* scene);
	~UIHud();

private:
	virtual void onStatsUpdated(EStatsType type) override;

private:
	Label* hpLabel = nullptr;
	Label* scoreLabel = nullptr;
	Stats* stats = nullptr;
};