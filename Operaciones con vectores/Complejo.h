#ifndef COMPLEJO_H
#define COMPLEJO_H

class Complejo : private Vector2D{
public:
	Complejo() : Vector2D(0, 0) {};
	Complejo(double x1, double y1): Vector2D(x1 , y1){};
private:
	friend Complejo operator*(const Complejo&, const Complejo&);
	friend std::ostream& operator<<(std::ostream&, Complejo const&);

};
#endif
