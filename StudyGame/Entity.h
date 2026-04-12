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

public:
	Entity();
	~Entity();

	bool isCanJump = false;

	void applyAcceleration(double deltaTime);

	Rect& getHitBox();
	Rect getHitBox() const;
	RigidBody& getRigiBody();
	Vector2 getVelocity() const;

	void applySpeed(Vector2 direction);

	
	void setVelocity(Vector2 _velocity);
	void setPosition(Vector2 position);

	const Stats getStats() { return this->statistics; }
	friend class BaseEntityPresenter;
};