#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include "atomo.h"

class Ensemble {
private:
int nAtom_;
std::vector<Atom> config_;
double Epsilon = 125.7;  //Kelvin
double Sigma = 0.03345; //A   //0.3345; // nm, 1e-9 m
double dt ; // MODIFICAR CUANDO EL PROGRAMA LEA
int Npas ; // MODIFICAR CUANDO EL PROGRAMA LEA
double DistanciaMaxLJ = 3.5;
Atom DimCaja ;
Atom DimCajaMin{0,0,0,0,0,0,0,"a"};
public:
    Ensemble();
    Ensemble(int, double, std::string, double, double, int);
    ~Ensemble();
    void Distancia3DVec(Atom atm1, Atom atm2, double& Distancia);
    void VecSum(Atom atm1, Atom atm2, Atom& DistanciaVec);
    void LennardJones(double& Potencial, double Distancia);
    void FuerzaLJ(double Distancia, Atom DistanciaVec, Atom& Fuerza);
    void PosVerlet(Atom PosIn, Atom& PosFin, Atom PosAnt, Atom Aceleracion);
    void VelVerlet(Atom& Velocidad, Atom PosFin, Atom PosAnt);
    void AceleracionVec(Atom& Aceleracion, Atom VelocidadIn, Atom VelocidadFin);
    //void temp(Atom rate, double& Ts);

    void Dinamica(Ensemble ens,int nAtom , int Npas);
};

#endif
