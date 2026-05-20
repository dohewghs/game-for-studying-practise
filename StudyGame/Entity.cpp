#include "Entity.h"
#include "IController.h"
#include "BaseEntityPresenter.h"
#include "Floor.h"

Entity::Entity(IEntityPresenter* _presenter) :
	hitBox(0, 0, 50, 50),
	rigidBody(),
	statistics(),
	weapon(),
	presenter(_presenter)
{
	this->presenter->setEntity(this);
}

Entity::~Entity()
{
	if (this->presenter)
		delete this->presenter;
}

void Entity::applyAcceleration(double deltaTime)
{
	this->rigidBody.applyAcceleration(deltaTime);
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

void Entity::setPresenter(IEntityPresenter* _presenter)
{
	this->presenter = _presenter;
}

void Entity::applySpeed(Vector2 direction)
{
	rigidBody.setAcceleration(direction * this->statistics.walkingSpeed * 7);
	
	this->presenter->setDirection(direction);

	if (direction.x != 0)
	{
		this->presenter->setAnimation("run");
	}
	else
	{
		this->presenter->setAnimation("idle");
	}
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

	this->presenter->present(renderer);

	this->weapon.present(renderer);
}

void Entity::update(double deltaTime)
{
	this->presenter->update(deltaTime);
	this->weapon.update(deltaTime);
}

void Entity::useWeapon()
{
	this->weapon.rotateAndUse();
}

bool Entity::isUsingWeapon()
{
	return this->weapon.isUsing();
}

void Entity::attack(Entity* enemy)
{
	Rect enemyRect = enemy->getHitBox();
	if (this->weapon.isHit(enemyRect))
	{
		enemy->applyDamage(this->weapon.getDamage() * this->statistics.damageCoef);
		//std::cout << "Intersection" << '\n';

		enemy->presenter->setAnimation("hurt");

	}
}

void Entity::applyDamage(double damagePoints)
{
	int hp = this->statistics.hp;

	hp = (hp >= damagePoints)? hp - damagePoints : 0;

	this->statistics.hp = hp;
}
