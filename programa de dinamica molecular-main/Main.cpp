
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <string>
#include <fstream> 
#include "atomo.h"
#include "ensemble.h"
#include "lectura.h"

int main(int argc, char **argv){

    int Npas {};
    int nAtom {};
    double mass {39.948}; //umas
    std::string name {"Argón"}; 
    double dt {1};
    int nPas {1};
    double BoxSize {5};
    double temp {300};
    bool termostat {0};

    parametros(argv, nAtom, BoxSize, temp, dt, nPas, termostat); 

    Ensemble Argon(nAtom, mass, name, dt, nPas, BoxSize);

    Argon.Dinamica(Argon,nAtom,Npas);

}
