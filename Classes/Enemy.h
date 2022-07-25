#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	explicit Enemy(const GameObjectSettings* data);

	virtual void startMove() override;

	bool isIgnoreWeapon() const { return ignoreUserWeapon; }

protected:
	virtual void onDestroyed() override;

private:
	int scorePoints = 0;
	bool ignoreUserWeapon = false;
};