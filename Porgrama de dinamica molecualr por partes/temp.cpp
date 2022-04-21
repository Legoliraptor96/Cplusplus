#include <iostream>
#include <vector>
#include <cmath>

void temp(std::vector<std::vector<double>>& rate, double& Ts, int nAtom){
               
// Evaluar la energía cinética promedio
               
    const double xmass{39.948}, avo {6.023e23}, m2kg {1.66e-27}, k {1.380649e-23};
    double Ek {};
               
    for(int i = 0; i < nAtom; ++i)
    Ek = (0.5*xmass*m2kg*(pow(rate[i][0],2) + pow(rate[i][1],2) + pow(rate[i][2],2)))/nAtom ;
               
    std::cout << "Energía cinética promedio " << Ek << std::endl;
               
// Temperatura 
               
    Ts = Ek/k ;
               
    std::cout << "Temperatura promedio " << Ts << std::endl;
               
               
} 

void termostat(std::vector<std::vector<double>>& rate, double& Ts, double& Te, int nAtom){

    double PEQUE {1e-6};

    while(abs(Ts-Te) > PEQUE){

    double ct = sqrt(Te/Ts) ;

    std::cout << "Factor de escalamiento " << ct  << std::endl ;

        for(int i = 0; i < nAtom; ++i){
              rate[i][0] = ct*rate[i][0];
              rate[i][1] = ct*rate[i][1];
              rate[i][2] = ct*rate[i][2];
         }

    temp(rate, Ts, nAtom);

    std::cout << "Nueva temperatura promedio " << Ts <<  std::endl;

    }

    std::cout << "Temperatura alcanzada " << Ts << std::endl;

}
