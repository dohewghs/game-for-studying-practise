
class Rect
{
public:
	double x;
	double y;
	double width;
	double height;

	Rect(double _x = 0, double _y = 0, double _width = 0, double _height = 0);

	Rect(const Rect& other);

	Rect& operator=(const Rect& other) = default;

	~Rect() = default;

	static bool HasIntersection(const Rect& first, const Rect& second);
};