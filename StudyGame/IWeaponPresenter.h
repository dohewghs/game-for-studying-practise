#pragma once
class Weapon;

class IWeaponPresenter
{
public:
	virtual void present(SDL_Renderer* renderer, const Weapon* weapon) = 0;
};