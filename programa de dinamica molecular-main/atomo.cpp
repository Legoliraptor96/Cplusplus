#include <iostream>
#include <vector>
#include <string>
#include "atomo.h"

Atom::Atom(): coordX_{0}, coordY_{0}, coordZ_{0},
              velX_{0}, velY_{0}, velZ_{0},
              mass_{0}, name_{" "} {
    std::cout << "Creando átomo en el origen " << std::endl;
}

Atom::Atom(double coordX, double coordY, double coordZ,
           double velX, double velY, double velZ,
           double mass, std::string name):
           coordX_{coordX}, coordY_{coordY}, coordZ_{coordZ},
           velX_{velX}, velY_{velY}, velZ_{velZ},
           mass_{mass}, name_{name} {
    std::cout << "Creando átomo con ciertos valores " << std::endl;
}

Atom::~Atom(){}

void Atom::imprimir(){
    std::cout << "Coordenadas " << std::endl;
    std::cout << "(" << coordX_ << ", " << coordY_
              << ", " << coordZ_ << ")" << std::endl;
    std::cout << "Velocidades " << std::endl;
    std::cout << "(" << velX_ << ", " << velY_
              << ", " << velZ_ << ")" << std::endl;
}              
