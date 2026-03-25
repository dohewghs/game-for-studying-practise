#pragma once
#include "RigidBody.h"
#include "Rect.h"
#include "Stats.h"
#include "Weapon.h"
#include "IController.h"
#include "IEntityPresenter.h"

class Floor;

class Entity
{
private:
	RigidBody rigidBody;
	Rect hitBox;
	Stats statistics;
	Weapon weapon;
	IEntityPresenter* presenter;

public:
	Entity();
	~Entity();

	void update(Vector2 additionalForce, float deltaTime);
	void present();

	Rect& getHitBox();
	Rect getHitBox() const;
	void setVelocityY(double value);

};