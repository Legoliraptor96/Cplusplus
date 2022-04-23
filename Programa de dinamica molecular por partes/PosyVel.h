#ifndef POSYVEL_H
#define POSYVEL_H

//Funcion para calcular la distancia entre dos puntos para dar un escalar
void Distancia3DVec( const std::vector<double> , const std::vector<double> ,  std::vector<double>& );

//Funcion para calcular la distancia entre dos puntos para dar un vector
void VecSum(const std::vector<double>  , const std::vector<double> , std::vector<double>& );

//Funcion para calcular el Potencial de Lennard-Jonees a partir de las cosntantes y la distancia entre átomos
void LennardJones(const double , const double , std::vector<double>& , const std::vector<double> );


//Funcion para calcular la derivada del potencial de Lennard-Jonees a partir de las cosntantes y la distancia entre átomos
void FuerzaLJ( const double  , const double  , const std::vector<double> , const std::vector<double>  ,std::vector<double>& );

//Función para calcular las posiciones según el algoritmo de Verlet
void PosVerlet( std::vector<double>& , std::vector<double>& , std::vector<double>& , const std::vector<double>  , const double );

//Función para calcular las velocidades según el algoritmo de Verlet
void VelVerlet(std::vector<double>& , const std::vector<double> ,const std::vector<double> , const double );


//funcion para calcular la aceleracion a partir de las velocidades
void AceleracionVec(std::vector<double>&  ,const std::vector<double> , const std::vector<double> , const double );



void Din2Atm(std::vector<double>& , std::vector<double>& , std::vector<double>&, std::vector<double>& ,
			const double, const double , std::vector<double> ,std::vector<double>& ,
			 std::vector<double>& , std::vector<double>& , 
			 std::vector<double>& , std::vector<double>& ,
			 std::vector<double>& ,std::vector<double>&  , const double, const std::vector<double> ,const std::vector<double> ,
			 std::vector<double>& , std::vector<double>& ,
			 std::vector<double>& , std::vector<double>& ,const size_t 
			 );


void PrimerPaso(std::vector<double>& , std::vector<double>& , std::vector<double>&, std::vector<double>& ,
			const double, const double , std::vector<double> ,std::vector<double>& ,
			 std::vector<double>& , 
			 std::vector<double>& ,
			 std::vector<double>& ,std::vector<double>&  , const double, const std::vector<double> ,const std::vector<double> ,
			 std::vector<double>& , std::vector<double>& ,
			 std::vector<double>& , std::vector<double>& 
			 );


void Dinamica(std::vector<double>  , std::vector<double>  , std::vector<double> ,std::vector<double> , 
			const std::vector<double> , const std::vector<double>, const double  , const double ,
			const double , const double );


#endif