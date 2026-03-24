struct Stats
{
	int hp;
	int maxHp;

	double luck;
	double damageCoef;
	double walkingSpeed;
	double attackSpeed;

	Stats() :
		hp(100),
		maxHp(100),
		luck(1.0),
		damageCoef(1.0),
		walkingSpeed(1.0),
		attackSpeed(1.0)
	{
	};
};