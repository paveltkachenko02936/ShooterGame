#pragma once
#include "GameObject.h"

class PlayerShip;

class Rocket : public GameObject
{
public:
	explicit Rocket(const GameObjectSettings* data);

	virtual void startMove() override;
};