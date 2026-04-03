#include "PhysicsEngine.h"
#include "Floor.h"

void PhysicsEngine::update(std::vector<Entity*>& entities, const Floor& floor, float deltaTime)
{
	for (Entity* entity : entities)
	{
		entity->applyImpulse(this->gravityScale);
		entity->update({ 0,0 }, 0.1);
	}

	this->updateCollisions(entities, floor);
}

void PhysicsEngine::updateCollisions(std::vector<Entity*>& entities, const Floor& floor)
{
	for (Entity* entity : entities)
	{
		Rect& hitBox = entity->getHitBox();

		if (floor.updateGroundCollision(hitBox))
		{
			entity->getRigiBody().setVelocityY(0);
		}
	}
}

bool PhysicsEngine::canJump(const Entity& entity, const Floor& floor)
{
	Rect sensor = entity.getHitBox();
	sensor.y += 1;

	return floor.hasIntersection(sensor);
}

