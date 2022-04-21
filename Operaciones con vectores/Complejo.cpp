#include <iostream>
#include "Vector2D.h"

class Complejo : private Vector2D{
public:
	Complejo() : Vector2D(0, 0) {};
	Complejo(double x1, double y1): Vector2D(x1 , y1){};
private:
	friend Complejo operator*(const Complejo&, const Complejo&);
	friend std::ostream& operator<<(std::ostream&, Complejo const&);
};

Complejo operator*(Complejo const& Vec1, Complejo const& Vec2){
	return Complejo{(Vec1.x_ * Vec2.x_)-(Vec1.y_ * Vec2.y_),
				    (Vec1.x_ * Vec2.y_)+(Vec1.y_*Vec2.x_) };
}

std::ostream& operator<<(std::ostream& as, Complejo const& a){
	as << a.x_ << " , " << a.y_ << " i" ;
	return as;
}
