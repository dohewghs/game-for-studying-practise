#include "PhysicsEngine.h"
#include "Floor.h"

void PhysicsEngine::update(std::vector<Entity*>& entities, const Floor& floor, float deltaTime)
{
	for (Entity* entity : entities)
	{
		entity->update(this->gravityScale, deltaTime);
	}

	this->updateCollisions(entities, floor);
}

void PhysicsEngine::updateCollisions(std::vector<Entity*>& entities, const Floor& floor)
{
	for (Entity* entity : entities)
	{
		Rect& hitBox = entity->getHitBox();

		if (floor.CollisionsY(hitBox, entity->getVelocity().y))
			entity->setVelocityY(0);

		if (floor.CollisionsX(hitBox, entity->getVelocity().x))
			entity->setVelocityX(0);
	}
}

bool PhysicsEngine::canJump(const Entity& entity, const Floor& floor)
{
	Rect sensor = entity.getHitBox();
	sensor.y += 1;

	return floor.hasIntersection(sensor);
}

