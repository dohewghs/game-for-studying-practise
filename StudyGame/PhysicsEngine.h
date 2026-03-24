#pragma once
#include <vector>
#include "Entity.h"
class Floor;

class PhysicsEngine
{
private:
	Vector2 gravityScale{ 0, 10 };

public:
	void update(std::vector<std::unique_ptr<Entity>>& entities, const Floor& floor, float deltaTime);
	void updateCollisions(std::vector<std::unique_ptr<Entity>>& entities, const Floor& floor);

	bool canJump(const Entity& entity, const Floor& floor);
};