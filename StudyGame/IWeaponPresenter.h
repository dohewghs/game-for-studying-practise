#pragma once
class Weapon;

class IWeaponPresenter
{
public:
	virtual ~IWeaponPresenter() = default;

	virtual void present(SDL_Renderer* renderer, const Weapon* weapon) = 0;
};