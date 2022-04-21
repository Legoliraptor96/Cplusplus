#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <random>
#include "ensemble.h"
#include "atomo.h"

Ensemble::Ensemble(): nAtom_{1}  {
    config_.resize(nAtom_);
    config_[1] = {0, 0, 0, 0, 0, 0, 1, " "} ;
               
    std::cout << "Ensemble default creado " << std::endl;
}              

Ensemble::Ensemble(int nAtom, double mass, std::string name, double det,
                   double BoxSize, int Npaso): nAtom_{nAtom}, dt{det},
                   Npas{Npaso} {
    config_.resize(nAtom_);
               
    std::cout << "Conjunto aleatorio de " << nAtom_ << " átomos"
              << std::endl;
               
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_real_distribution<double> distC(0.,5.);
    std::uniform_real_distribution<double> distV(0.,5.);
               
    for(int i = 0; i < nAtom; i++){
         config_[i].coordX_ = distC(generator);
         config_[i].coordY_ = distC(generator);
         config_[i].coordZ_ = distC(generator);
         config_[i].velX_ = distV(generator);
         config_[i].velY_ = distV(generator);
         config_[i].velZ_ = distV(generator);
         config_[i].mass_ = mass ;
         config_[i].name_ = name ;
               
         config_[i].imprimir();
    }          
               
    DimCaja.coordX_ = BoxSize;
    DimCaja.coordY_ = BoxSize;
    DimCaja.coordZ_ = BoxSize;
               
} 

Ensemble::~Ensemble() {
    std::cout << "Limpiando " << std::endl;
}              
               
               
void Ensemble::Distancia3DVec(Atom atm1, Atom atm2, double& Distancia){
    Distancia = sqrt(pow((atm1.coordX_ - atm2.coordX_), 2) +
                     pow((atm1.coordY_ - atm2.coordY_), 2) +
                     pow((atm1.coordZ_ - atm2.coordZ_), 2));
   // std::cout << Distancia << std::endl;
}              
               
void Ensemble::VecSum(Atom atm1, Atom atm2, Atom& DistanciaVec){
    DistanciaVec.coordX_ =  atm1.coordX_  + atm2.coordX_ ;
    DistanciaVec.coordY_ =  atm1.coordY_  + atm2.coordY_ ;
    DistanciaVec.coordZ_ =  atm1.coordZ_  + atm2.coordZ_ ;
}

void Ensemble::LennardJones(double& Potencial, double Distancia){
    Potencial=4*Epsilon*(pow((Sigma/Distancia),12) - pow((Sigma/Distancia),6));
}              
               
void Ensemble::FuerzaLJ(double Distancia, Atom DistanciaVec, Atom& Fuerza){
    Fuerza.coordX_ = std::abs(4*Epsilon*(12*pow(Sigma,12)/pow(Distancia,13) -
                     6* pow(Sigma,6)/pow(Distancia,7))*DistanciaVec.coordX_);
               
    Fuerza.coordY_ = std::abs(4*Epsilon*(12*pow(Sigma,12)/pow(Distancia,13) -
                     6* pow(Sigma,6)/pow(Distancia,7))*DistanciaVec.coordY_);
               
    Fuerza.coordZ_ = std::abs(4*Epsilon*(12*pow(Sigma,12)/pow(Distancia,13) -
                     6* pow(Sigma,6)/pow(Distancia,7))*DistanciaVec.coordZ_);
}              
               
void Ensemble::PosVerlet(Atom PosIn, Atom& PosFin, Atom PosAnt, Atom Aceleracion){
    //\vec{x}(t + \Delta t) = 2\vec{x}(t) - \vec{x}(t - \Delta t) + \vec{a}(t) \Delta t^2 + O(\Delta t^4)
    //Vzzlzrt, L. (1967). “Exyeriments” on Classical Fluids. I. Thermodynamical Properties of Lennard,-Jones Molecules~.
    PosFin.coordX_ = 2*PosIn.coordX_ - PosAnt.coordX_ + Aceleracion.velX_*pow(dt,2);
    PosFin.coordY_ = 2*PosIn.coordY_ - PosAnt.coordY_ + Aceleracion.velY_*pow(dt,2);
    PosFin.coordZ_ = 2*PosIn.coordZ_ - PosAnt.coordZ_ + Aceleracion.velZ_*pow(dt,2);
} 

void Ensemble::VelVerlet(Atom& Velocidad, Atom PosFin, Atom PosAnt){
    //\vec{v}(t) = [ \vec{x}(t + \Delta t) - \vec{x}(t - \Delta t)] / (2 \Delta t)
    //Vzzlzrt, L. (1967). “Exyeriments” on Classical Fluids. I. Thermodynamical Properties of Lennard,-Jones Molecules~.
    Velocidad.velX_ = (PosFin.coordX_ - PosAnt.coordX_)/(2*dt);
    Velocidad.velY_ = (PosFin.coordY_ - PosAnt.coordY_)/(2*dt);
    Velocidad.velZ_ = (PosFin.coordZ_ - PosAnt.coordZ_)/(2*dt);
}              
               
void Ensemble::AceleracionVec(Atom& Aceleracion, Atom VelocidadIn, Atom VelocidadFin){
    Aceleracion.velX_ = (VelocidadFin.velX_ - VelocidadIn.velX_)/dt;
    Aceleracion.velY_ = (VelocidadFin.velY_ - VelocidadIn.velY_)/dt;
    Aceleracion.velZ_ = (VelocidadFin.velZ_ - VelocidadIn.velZ_)/dt;
}

void Ensemble::Dinamica(Ensemble ens, int nAtom, int Npas){
   double Distancia;
    double Potencial;
    Atom DistanciaVec;
    Atom Fuerza;
    double mass {39.948}; //umas
    std::string name {"Argón"};
    Ensemble VelocidadFin(nAtom,mass,name, 1, 1, 1);
    Ensemble PosAnt(nAtom,mass,name, 1, 1, 1);
    Ensemble Aceleracion(nAtom,mass,name, 1, 1, 1);
    Ensemble VelocidadIn(nAtom,mass,name, 1, 1, 1);
    Ensemble PosFin(nAtom,mass,name, 1, 1, 1);
    std::string s{"try.txt"};
   //  s.push_back(**argv);
     //std::ofstream fs("coord.txt");
    std::fstream f;
    std::ofstream fout;
    std::ifstream fin;
    fin.open("try.txt");
    fout.open ("try.txt", std::ios::app);


    for (int i = 0; i < Npas; ++i){
         for(size_t iAtom = 0; iAtom < nAtom ; ++iAtom){
              for(size_t jAtom = iAtom+1 ; jAtom < nAtom ; ++jAtom){
                Distancia3DVec(ens.config_[iAtom],ens.config_[jAtom],Distancia);
                if(Npas = 0){
                    if(Distancia < DistanciaMaxLJ){
                        LennardJones(Potencial, Distancia);
                        VecSum(ens.config_[iAtom], ens.config_[jAtom], DistanciaVec);
                        FuerzaLJ(Distancia, DistanciaVec, Fuerza);

                        (VelocidadFin.config_[jAtom]).velX_ = (Fuerza.coordX_ * dt )
                                                             + (ens.config_[jAtom]).velX_;
               
                        (VelocidadFin.config_[jAtom]).velY_ = (Fuerza.coordY_ * dt )
                                                              + (ens.config_[jAtom]).velY_;
               
                        (VelocidadFin.config_[jAtom]).velZ_ = (Fuerza.coordZ_ * dt )
                                                              + (ens.config_[jAtom]).velZ_;
               
                        (PosAnt.config_[jAtom]).coordX_ =  (ens.config_[jAtom]).coordX_;
                        (PosAnt.config_[jAtom]).coordY_ =  (ens.config_[jAtom]).coordY_;
                        (PosAnt.config_[jAtom]).coordZ_ =  (ens.config_[jAtom]).coordZ_;
               
                        (ens.config_[jAtom]).coordX_ = (ens.config_[jAtom]).coordX_
                                                       + ((VelocidadFin.config_[jAtom]).velX_*dt);
               
                        (ens.config_[jAtom]).coordY_ = (ens.config_[jAtom]).coordY_
                                                       + ((VelocidadFin.config_[jAtom]).velY_*dt);
               
                        (ens.config_[jAtom]).coordZ_ = (ens.config_[jAtom]).coordZ_
                                                       + ((VelocidadFin.config_[jAtom]).velZ_*dt);
               
               
                        if((ens.config_[jAtom]).coordX_  > DimCaja.coordX_){
                            (ens.config_[jAtom]).coordX_ = DimCajaMin.coordX_
                            + (ens.config_[jAtom]).coordX_ - DimCaja.coordX_ ;
                        }
                        
                        if((ens.config_[jAtom]).coordY_  > DimCaja.coordY_){
                            (ens.config_[jAtom]).coordY_ = DimCajaMin.coordY_
                            + (ens.config_[jAtom]).coordY_ - DimCaja.coordY_ ;
                        }
               
                        if((ens.config_[jAtom]).coordZ_  > DimCaja.coordZ_){
                           (ens.config_[jAtom]).coordZ_ = DimCajaMin.coordZ_
                           + (ens.config_[jAtom]).coordZ_ - DimCaja.coordZ_ ;
                        }
               
                        if((ens.config_[jAtom]).coordX_  < DimCaja.coordX_){
                        (ens.config_[jAtom]).coordX_ = DimCajaMin.coordX_
                        - std::abs((ens.config_[jAtom]).coordX_ - DimCaja.coordX_);
                        }
               
                        if((ens.config_[jAtom]).coordY_  < DimCaja.coordY_){
                        (ens.config_[jAtom]).coordY_ = DimCajaMin.coordY_
                        - std::abs((ens.config_[jAtom]).coordY_ - DimCaja.coordY_);
                        }
               
                        if((ens.config_[jAtom]).coordZ_  < DimCaja.coordY_){
                        (ens.config_[jAtom]).coordZ_ = DimCajaMin.coordZ_
                        - std::abs((ens.config_[jAtom]).coordZ_ - DimCaja.coordZ_ );
                        }
               
                        AceleracionVec(Aceleracion.config_[jAtom], ens.config_[jAtom],
                                       VelocidadFin.config_[jAtom]);

   //fout << (ens.config_[jAtom]).coordX_ << "  "  
    //     << (ens.config_[jAtom]).coordY_ << "  " << 
    //     (ens.config_[jAtom]).coordY_ << std::endl;    
                       fout << "hola" << std::endl;
               
               
               
                     //temp(rate,Ts,nAtom);
                    }
                    else{
                   		fout << "hola" << std::endl;
                    //temp(rate,Ts,nAtom);
                    }
                }
                else{
                     Distancia3DVec(ens.config_[iAtom], ens.config_[jAtom],Distancia);
                     if(Distancia < DistanciaMaxLJ){
                     LennardJones(Potencial,  Distancia);
                     VecSum(ens.config_[iAtom], ens.config_[jAtom], DistanciaVec);
                     FuerzaLJ(Distancia, DistanciaVec, Fuerza);
                     PosVerlet(ens.config_[jAtom], PosFin.config_[jAtom],
                     PosAnt.config_[jAtom], Aceleracion.config_[jAtom]);
                     VelVerlet(VelocidadFin.config_[jAtom], PosFin.config_[jAtom],
                     PosAnt.config_[jAtom]);
                     AceleracionVec(Aceleracion.config_[jAtom], ens.config_[jAtom],
                     VelocidadFin.config_[jAtom]);

                     if((PosFin.config_[jAtom]).coordX_  > DimCaja.coordX_){
                        (PosFin.config_[jAtom]).coordX_ = DimCajaMin.coordX_ +
                        (PosFin.config_[jAtom]).coordX_ - DimCaja.coordX_;
               
                        (PosAnt.config_[jAtom]).coordX_ = DimCajaMin.coordX_ +
                        (PosAnt.config_[jAtom]).coordX_ - DimCaja.coordX_;
               
                        (ens.config_[jAtom]).coordX_ = DimCajaMin.coordX_ +
                        (ens.config_[jAtom]).coordX_    - DimCaja.coordX_;
                     }
               
                     if((PosFin.config_[jAtom]).coordY_ > DimCaja.coordY_ ){
                        (PosFin.config_[jAtom]).coordY_ = DimCajaMin.coordY_ +
                        (PosFin.config_[jAtom]).coordY_ - DimCaja.coordY_;
               
                        (PosAnt.config_[jAtom]).coordY_ = DimCajaMin.coordY_ +
                        (PosAnt.config_[jAtom]).coordY_ - DimCaja.coordY_;
               
                        (ens.config_[jAtom]).coordY_ = DimCajaMin.coordY_ +
                        (ens.config_[jAtom]).coordY_    - DimCaja.coordY_;
                     }
               
                     if((PosFin.config_[jAtom]).coordZ_  > DimCaja.coordZ_){
                        (PosFin.config_[jAtom]).coordZ_ = DimCajaMin.coordZ_ +
                        (PosFin.config_[jAtom]).coordZ_ - DimCaja.coordZ_;
               
                        (PosAnt.config_[jAtom]).coordZ_ = DimCajaMin.coordZ_ +
                        (PosAnt.config_[jAtom]).coordZ_ - DimCaja.coordZ_;
               
                        (ens.config_[jAtom]).coordZ_    = DimCajaMin.coordZ_ +
                        (ens.config_[jAtom]).coordZ_    - DimCaja.coordZ_;
                     }

                     if((PosFin.config_[jAtom]).coordX_ < DimCaja.coordX_){
                        (PosFin.config_[jAtom]).coordX_ = DimCaja.coordX_ -
                        std::abs((PosFin.config_[jAtom]).coordX_ - DimCajaMin.coordX_);

                        (PosAnt.config_[jAtom]).coordX_ = DimCaja.coordX_ -
                        std::abs((PosAnt.config_[jAtom]).coordX_ - DimCajaMin.coordX_);

                        (ens.config_[jAtom]).coordX_ = DimCaja.coordX_ -
                        std::abs((ens.config_[jAtom]).coordX_ - DimCajaMin.coordX_);
                     }

                     if((PosFin.config_[jAtom]).coordY_ < DimCaja.coordY_){
                        (PosFin.config_[jAtom]).coordY_ = DimCaja.coordY_ -
                        std::abs((PosFin.config_[jAtom]).coordY_ - DimCajaMin.coordY_ );

                        (PosAnt.config_[jAtom]).coordY_ = DimCaja.coordY_ -
                        std::abs((PosAnt.config_[jAtom]).coordY_ - DimCajaMin.coordY_ );

                        (ens.config_[jAtom]).coordY_ = DimCaja.coordY_ -
                        std::abs((ens.config_[jAtom]).coordY_ - DimCajaMin.coordY_ );
                     }

                     if((PosFin.config_[jAtom]).coordZ_  < DimCaja.coordZ_){
                        (PosFin.config_[jAtom]).coordZ_ = DimCaja.coordZ_ -
                        std::abs((PosFin.config_[jAtom]).coordZ_ - DimCajaMin.coordZ_ );

                        (PosAnt.config_[jAtom]).coordZ_ = DimCaja.coordZ_ -
                        std::abs((PosAnt.config_[jAtom]).coordZ_ - DimCajaMin.coordZ_ );

                        (ens.config_[jAtom]).coordZ_ = DimCaja.coordZ_ -
                        std::abs((ens.config_[jAtom]).coordZ_ - DimCajaMin.coordZ_ );
                     }
                                            fout << "hola" << std::endl;
                     }
   else{
                        //temp(VelocidadFin,Ts,nAtom);
   	                       fout << "hola" << std::endl;
                     }
                     //temp(VelocidadFin,Ts,nAtom);
                }
             } 
         }     
    }          
    fin.close();
    fout.close();
}              
  
