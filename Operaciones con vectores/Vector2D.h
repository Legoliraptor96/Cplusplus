#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D{
public:
	double x_;
	double y_;
	Vector2D(double x1, double y1):x_{x1}, y_{y1}{};
	Vector2D() : Vector2D(0,0){};
	~Vector2D();
private:
	friend Vector2D operator+(const Vector2D&, const Vector2D&);
	friend std::ostream& operator<<(std::ostream&, Vector2D const&);
};

#endif
