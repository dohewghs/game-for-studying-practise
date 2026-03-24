struct Stats
{
	int hp;
	int maxHp;

	double luck;
	double damageCoef;
	double speedCoef;
	double attackSpeed;

	Stats() :
		hp(100),
		maxHp(100),
		luck(1.0),
		damageCoef(1.0),
		speedCoef(1.0),
		attackSpeed(1.0)
	{
	};
};