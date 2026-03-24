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
	IController* contorller;
	IEntityPresenter* presenter;

public:
	Entity();
	~Entity();

	void move(Vector2 direction, float deltaTime);
	void update(Vector2 additionalForce, float deltaTime);
	void present();

	Rect& getHitBox();
	Rect getHitBox() const;
	void setVelocityY(double value);

};