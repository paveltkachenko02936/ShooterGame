#pragma once
#include <list>

enum class EStatsType
{
	UserHP,
	Score
};

class StatsListener
{
public:
	virtual void onStatsUpdated(EStatsType type) {};
};


class Stats final
{
public:
	int getUserHP() const { return health; }
	int getScore() const { return score; }

	void updateUserHP(int newValue);
	void updateScore(int value);

	void addListener(StatsListener* listener);
	void removeListener(StatsListener* listener);

	void emitUpdated(EStatsType type);

private:
	std::list<StatsListener*> listeners;

	int health = 0;
	int score = 0;
};