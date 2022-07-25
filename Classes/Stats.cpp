#include "Stats.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

void Stats::updateUserHP(int newValue)
{
	health = std::max(0, newValue);
	emitUpdated(EStatsType::UserHP);
}

void Stats::updateScore(int value)
{
	score += value;
	emitUpdated(EStatsType::Score);
}

void Stats::addListener(StatsListener* listener)
{
	auto found = std::find(listeners.begin(), listeners.end(), listener);
	if (found == listeners.end())
		listeners.push_back(listener);
}

void Stats::removeListener(StatsListener* listener)
{
	auto it = std::remove(listeners.begin(), listeners.end(), listener);
	if (it != listeners.end())
		listeners.erase(it);
}

void Stats::emitUpdated(EStatsType type)
{
	for (auto listener : listeners)
		listener->onStatsUpdated(type);
}
