#include "Entity.h"
#include "IController.h"
#include "BaseEntityPresenter.h"
#include "Floor.h"

Entity::Entity() :
	hitBox(0, 0, 50, 50),
	rigidBody(),
	statistics(),
	weapon()
{
	this->presenter = new BaseEntityPresenter();
}

Entity::~Entity()
{
	if (this->presenter)
		delete this->presenter;
}

void Entity::applyAcceleration(double deltaTime)
{
	this->rigidBody.applyAcceleration(deltaTime);
	this->weapon.update(deltaTime);
}

Rect& Entity::getHitBox() {	return this->hitBox; }

Rect Entity::getHitBox() const
{
	return this->hitBox;
}

RigidBody& Entity::getRigiBody()
{
	return this->rigidBody;
}

void Entity::applySpeed(Vector2 direction)
{
	rigidBody.setAcceleration(direction * this->statistics.walkingSpeed);
}

Vector2 Entity::getVelocity() const
{
	return this->rigidBody.getVelocity();
}

void Entity::setVelocity(Vector2 _velocity)
{
	this->rigidBody.setVelocity(_velocity);
}

void Entity::setPosition(Vector2 position)
{
	this->hitBox.x = position.x;
	this->hitBox.y = position.y;

	this->weapon.setCoords(position += {30, 30});
}

void Entity::present(SDL_Renderer* renderer)
{
	if (!this->presenter)
		return;

	this->presenter->present(renderer, this);

	this->weapon.present(renderer);
}

void Entity::useWeapon()
{
	this->weapon.rotateAndUse();
}

bool Entity::isUsingWeapon()
{
	return this->weapon.isUsing();
}

void Entity::attack(Entity* entity)
{
	Rect enemyRect = entity->getHitBox();
	if (this->weapon.isHit(enemyRect))
	{
		entity->applyDamage(this->weapon.getDamage() * this->statistics.damageCoef);
		std::cout << "YYYYYEEEEEEEEEEEEEEEE" << '\n';

	}
}

void Entity::applyDamage(double damagePoints)
{
	int hp = this->statistics.hp;

	hp = (hp >= damagePoints)? hp - damagePoints : 0;

	this->statistics.hp = hp;
}
