#pragma once
#include "GameObject.h"

class PlayerShip : public GameObject
{
public:
	explicit PlayerShip(const GameObjectSettings* data);
	virtual void moveBy(float dx, float dy) override;

	virtual void startAction() override;
	virtual void stopAction() override;

protected:
	virtual void emitHPUpdated() override;

private:
	void launchRocket();
};