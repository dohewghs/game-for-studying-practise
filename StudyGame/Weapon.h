
class Entity;

class Weapon
{
private:
	double damage;
public:
	Weapon() :
		damage(10)
	{ };
	~Weapon() = default;
	
	void use(Entity entity);
};