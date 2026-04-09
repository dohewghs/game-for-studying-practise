#pragma once
#include <vector>
#include "Entity.h"
class Floor;

class PhysicsEngine
{
private:
	Vector2 gravityScale{ 0, 9.81 };

public:
	void update(std::vector<Entity*>& entities, const Floor& floor, float deltaTime);
	void updateCollisions(std::vector<Entity*>& entities, const Floor& floor);

	void handleInput(Entity& entity, Vector2& direction, const Floor& floor);

	bool canJump(const Entity& entity, const Floor& floor);
};