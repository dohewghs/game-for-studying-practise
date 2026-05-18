#pragma once
#include "BaseWeaponPresenter.h"
#include "Vector2.h"

class Entity;

class Weapon
{
private:
	double damage;

	Rect hitBox;
	double angle;
	bool rotateWeapon;

	IWeaponPresenter* presenter;

	bool isNowUsing;

public:
	Weapon();
	~Weapon();
	
	double getDamage() const;

	void update(double deltaTime);
	void present(SDL_Renderer* renderer);

	void setCoords(Vector2 coords);

	void rotateAndUse();

	bool isUsing();

	bool isHit(const Rect& rect);
};