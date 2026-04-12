#include "Weapon.h"
#include "Entity.h"

void Weapon::update(double deltaTime)
{
	if (this->rotateWeapon)
	{
		this->angle += 5 * deltaTime;
	}

	if (angle > 110)
	{
		angle = 0;
		this->rotateWeapon = false;
	}
}

void Weapon::setCoords(Vector2 coords)
{
	this->hitBox.x = coords.x;
	this->hitBox.y = coords.y;
}

void Weapon::present(SDL_Renderer* renderer)
{
	if (!this->presenter)
		return;

	this->presenter->present(renderer, this);
}

void Weapon::rotate()
{
	if (this->rotateWeapon)
		return;

	this->rotateWeapon = true;
}
