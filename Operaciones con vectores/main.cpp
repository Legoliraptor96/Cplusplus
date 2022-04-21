#include <iostream>
#include "Vector2D.h"
#include "Complejo.h"
int main() {
Vector2D vect1;
Vector2D vect2 {-4.5, 8.6};
Vector2D vect3 {11.42, 0.84};
std::cout << vect1 << "\n";
std::cout << vect2 + vect3 << "\n";
Complejo cmplx1;
Complejo cmplx2 {-3.2, 5.75};
Complejo cmplx3 {10.12, 1.17};
std::cout << cmplx1 << "\n";
std::cout << cmplx2*cmplx3 << std::endl;
}
