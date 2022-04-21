#include <iostream>

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


Vector2D operator+(Vector2D const& Vec1, Vector2D const& Vec2){
	return Vector2D{Vec1.x_ + Vec2.x_,
				    Vec1.y_ + Vec2.y_};
}

std::ostream& operator<<(std::ostream& as, Vector2D const& a){
	as << a.x_ << " , " << a.y_;
	return as;
}

Vector2D::~Vector2D(){
}

