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
	IEntityPresenter* presenter;

public:
	Entity();
	~Entity();

	void update(Vector2 additionalForce, float deltaTime);
	void present(SDL_Renderer* renderer);

	Rect& getHitBox();
	Rect getHitBox() const;
	void setVelocityY(double value);

	friend class BaseEntityPresenter;
};