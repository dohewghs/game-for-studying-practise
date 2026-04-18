#include "PhysicsEngine.h"
#include "Floor.h"

std::pair<Vector2, Vector2> PhysicsEngine::getAvailableMovement(Entity& entity, const Floor& floor, double deltaTime)
{
	double GRAVITY_SCALE = 9.81 * 0.1;

	Vector2 finalVelocity = entity.getVelocity();
	finalVelocity.y += GRAVITY_SCALE * deltaTime;
	
	Rect testHitBox = Rect(entity.getHitBox());


	testHitBox.x += finalVelocity.x * deltaTime;

	if (floor.CollisionsX(testHitBox, finalVelocity.x))
		finalVelocity.x = 0;

	testHitBox.y += (finalVelocity.y) * deltaTime;

	if (floor.CollisionsY(testHitBox, finalVelocity.y))
	{
		finalVelocity.y = 0;
	}
		
	
	return { Vector2(testHitBox.x, testHitBox.y), finalVelocity};
}

bool PhysicsEngine::canJump(const Entity& entity, const Floor& floor)
{
	Rect sensor = entity.getHitBox();
	sensor.y += 0.1;

	return floor.hasIntersection(sensor);
}

