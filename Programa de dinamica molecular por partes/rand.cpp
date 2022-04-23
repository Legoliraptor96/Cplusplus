// Crear una configuración inicial con random
// Velocidades

#include <iostream>
#include <random> 
#include <cmath>
#include <vector>
#include <iomanip>

void inicial(const double density, std::vector<std::vector<double>>& coord, 
             std::vector<std::vector<double>>& rate, int nAtom, 
             std::vector<double>& boxSize,std::vector<double>& boxSize2){
    
    // A partir de la densidad determinamos el número de átomos de Argón
    // Revisar porque no asigna valores correctamente 
/*
    const double A2m {1e-9}, BoxSize {1.}, xmass {39.948}, avo {6.023e23};

    int n = (density*pow(BoxSize,3)*avo)/(xmass) ;
    
    size_t  nAtom = round(n) ;


    std::cout << n << std::endl;
    std::cout << nAtom << std::endl;
    
*/    

    const double V_MAX {0.5}; 

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_real_distribution<double> dist(boxSize2[1], boxSize[1]);
    std::uniform_real_distribution<double> distv(0.,V_MAX);

    coord.resize(nAtom);
    rate.resize(nAtom);

    for(int i  = 0; i < nAtom; ++i){
         coord[i].resize(3) ;
         rate[i].resize(3) ;
    }
     
    std::cout << "Renglones " << coord.size() << std::endl;
    std::cout << "Columnas " << coord[0].size() << std::endl;

    
    // Construyendo matriz de coordenadas
    for (int i =0; i < nAtom; ++i){
         for (int j = 0; j < 3; ++j){
              coord[i][j] = dist(generator) ;  
         }
    }

   //  Construyendo matriz de velocidades
     for (int i = 0; i < nAtom; ++i){
         for (size_t j = 0; j < 3; ++j){
              rate[i][j] = distv(generator) ;  
         }
    }

}

void printMatrix(std::vector<std::vector<double>>& a){
    for(size_t i = 0; i < a.size(); ++i){
         for(size_t j = 0; j < a[i].size(); ++j){
              std::cout << std::setw(12) << std::setprecision(8) ;
              std::cout << a[i][j] ;
         }
         std::cout << std::endl;
    }
}

