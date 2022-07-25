#pragma once
#include <string>

class GameObject;

class GameObjectsFactory final
{
public:
	static GameObject* createObject(const std::string& type);
};
