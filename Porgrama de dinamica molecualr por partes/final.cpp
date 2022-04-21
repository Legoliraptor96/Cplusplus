#include <iostream>
#include <cmath>
#include <vector>
#include "PosyVel.h"
#include "rand.h"
#include "temp.h"

//Programa de Dinamica molecular Alonso Jacobo

int main(){

	double EpsAr = 125.7; //Kelvin 
	double SigmaAr = 0.03345 ;//A   //0.3345; // nm, 1e-9 m  
    double density {1.0} ; // Atomos/A^3 En proceso
    double Ts {}, Te {5000}; //K
    int nAtom = 10 ;

	//	 double Masa= 39.948; // Masa del argon en ua //6.633520E-26 ;//masa del Argon en kilogramos
	 size_t Npas = 5 ; //numero de pasos para posiciones de verlet
	 double dt=0.1; //delta de tiempo en segundos

	// White, J. A. (1999). Lennard-Jones as a model for argon and test of extended renormalization group calculations

    // Matrices de coordenadas y velocidades
    std::vector<std::vector<double>> coord ;
    std::vector<std::vector<double>> rate ;

	 //Vectores  con información que debe ser dada
     std::vector<double> atm1(3,0);
	 std::vector<double> atm2(3,0);
	 std::vector<double> VelocidadIn(3,0) ;
	 std::vector<double> VelocidadIn2(3,0);
	 std::vector<double> DimCaja{5,5,5} ;
	 std::vector<double> DimCajaMin{0,0,0} ;

     // Se adapta el ciclo por lo mientras 
    
    inicial(density, coord, rate, nAtom, DimCaja , DimCajaMin) ;

    std::cout << "Matriz de coordenadas " << std::endl ;
    printMatrix(coord) ;
    std::cout << "Matriz de velocidades " << std::endl ;
    printMatrix(rate) ;

    temp(rate, Ts, nAtom) ;
    
    for(int i = 0; i < nAtom; ++i){

         atm1 = coord[i] ;
         VelocidadIn = rate[i] ;

         for(int j = i+1; j < nAtom; ++j){

         atm2 = coord[j];
         VelocidadIn2 = rate[j] ;

         Dinamica(atm1 , atm2 , VelocidadIn, VelocidadIn2, DimCaja, DimCajaMin, EpsAr, SigmaAr, Npas, dt);    
         }
    }

    termostat(rate, Ts, Te, nAtom);
}



