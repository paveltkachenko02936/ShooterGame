#pragma once
#include "GameSettings.h"
#include "cocos2d.h"

class GameObject : public cocos2d::Sprite
{
public:
	explicit GameObject(const GameObjectSettings* data);

	virtual void startMove() {};
	virtual void moveBy(float dx, float dy) {};
	virtual void hit(int damage);

	virtual void startAction() {};
	virtual void stopAction() {};

	int getPower() const { return power; }
	int getHealth() const { return health; }
	int getSpeed() const { return speed; }

protected:
	virtual void onDestroyed() {};
	virtual void removeFromManager();
	virtual void emitHPUpdated() {};

protected:
	int speed = 0;
	int health = 0;
	int power = 0;
};