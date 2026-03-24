
class Vector2;

class IController
{
public:
	virtual void input() = 0;
	virtual Vector2 getInputDirection() = 0;
	virtual bool isJumpPressed() = 0;
};