#pragma once
#include <vector>
#include <list>

class GameObject;

class GameObjectsManager final
{
public:
	GameObjectsManager();
	~GameObjectsManager();

	void addEnemy(GameObject* obj);
	void addRocket(GameObject* obj);
	void assignPlayer(GameObject* obj) { player = obj; }

	void removeObject(GameObject* obj);

	GameObject* getPlayerObject() const { return player; }

private:
	void checkCollisions();
	bool checkCollision(const GameObject* first, const GameObject* second) const;
	bool checkIgnoreWeapon(GameObject* obj);

private:
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> rockets;
	GameObject* player = nullptr;
};