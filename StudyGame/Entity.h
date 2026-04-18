#pragma once
#include "RigidBody.h"
#include "Rect.h"
#include "Stats.h"
#include "Weapon.h"
#include "IController.h"
#include "IEntityPresenter.h"

class BaseEntityPresenter;

class Entity
{
private:
	RigidBody rigidBody;
	Rect hitBox;
	Stats statistics;
	Weapon weapon;

	IEntityPresenter* presenter = nullptr;
public:
	Entity();
	~Entity();

	bool isCanJump = false;

	void applyAcceleration(double deltaTime);

	Rect& getHitBox();
	Rect getHitBox() const;
	RigidBody& getRigiBody();
	Vector2 getVelocity() const;
	const Stats getStats() { return this->statistics; }

	void applySpeed(Vector2 direction);

	void setVelocity(Vector2 _velocity);
	void setPosition(Vector2 position);

	void present(SDL_Renderer* renderer);

	void useWeapon();
	bool isUsingWeapon();
	void attack(Entity* entity);
	void applyDamage(double damagePoints);

	friend class BaseEntityPresenter;
};