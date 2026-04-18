#include "Weapon.h"
#include "Entity.h"

double Weapon::getDamage() const
{
	return this->damage;
}

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
		this->isNowUsing = false;
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

void Weapon::rotateAndUse()
{
	if (this->rotateWeapon)
		return;

	this->rotateWeapon = true;
	this->isNowUsing = true;
}

bool Weapon::isUsing()
{
	return this->isNowUsing;
}

bool Weapon::isHit(const Rect& rect)
{
	if (HasIntersection(this->hitBox, rect))
	{
		this->isNowUsing = false;
		return true;
	}
	return false;
}
