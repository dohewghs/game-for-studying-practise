#include "PhysicsEngine.h"
#include "Floor.h"

void PhysicsEngine::update(std::vector<std::unique_ptr<Entity>>& entities, const Floor& floor, float deltaTime)
{
	for (std::unique_ptr<Entity>& entity : entities)
	{
		entity->update(this->gravityScale, deltaTime);
	}

	this->updateCollisions(entities, floor);
}

void PhysicsEngine::updateCollisions(std::vector<std::unique_ptr<Entity>>& entities, const Floor& floor)
{
	for (std::unique_ptr<Entity>& entity : entities)
	{
		Rect& hitBox = entity->getHitBox();

		if (floor.updateGroundCollision(hitBox))
		{
			entity->setVelocityY(0);
		}
		
	}
}

bool PhysicsEngine::canJump(Entity entity, const Floor& floor)
{
	Rect sensor = entity.getHitBox();
	sensor.y += 1;

	return floor.hasIntersection(sensor);
}

