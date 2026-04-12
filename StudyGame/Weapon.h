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

public:
	Weapon() :
		damage(10),
		hitBox({0,0,50,7}),
		angle(10),
		rotateWeapon(false),
		presenter(new BaseWeaponPresenter(&this->hitBox, &this->angle))
	{
	};

	~Weapon()
	{
		if (this->presenter)
			delete this->presenter;
	}
	
	void update(double deltaTime);

	void setCoords(Vector2 coords);

	void present(SDL_Renderer* renderer);

	void rotate();
};