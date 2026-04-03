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

	void update(Vector2 additionalForce, float deltaTime);

	Rect& getHitBox();
	Rect getHitBox() const;
	RigidBody& getRigiBody();
	void applyImpulse(Vector2 force);
	void applySpeed(Vector2 direction);

	friend class BaseEntityPresenter;
};