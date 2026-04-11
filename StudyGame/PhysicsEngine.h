#pragma once
#include <vector>
#include "Entity.h"
#include <iostream>

class Floor;

class PhysicsEngine
{
public:
	std::pair<Vector2, Vector2> getAvailableMovement(Entity& entity, const Floor& floor, double deltaTime);

	bool canJump(const Entity& entity, const Floor& floor);
};