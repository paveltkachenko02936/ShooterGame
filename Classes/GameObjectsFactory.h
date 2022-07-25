#pragma once
#include <string>

class GameObject;
class GameObjectSettings;

class GameObjectsFactory final
{
public:
	static GameObject* createObject(const std::string& type);
};
