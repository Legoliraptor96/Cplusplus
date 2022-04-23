
#include <iostream>
#include <cmath>
#include <vector>

void Distancia3DVec( const std::vector<double> atm1, const std::vector<double> atm2,  std::vector<double>& Distancia){

	Distancia[0] =  sqrt(pow((atm1[0]-atm2[0]),2)+pow((atm1[1]-atm2[1]),2)+pow((atm1[2]-atm2[2]),2));

	Distancia[0] = sqrt(pow(Distancia[0],2));

}




void VecSum(const std::vector<double> atm1 , const std::vector<double> atm2 , std::vector<double>& DistanciaVec){
	for (size_t i = 0;  atm1.size() > i ; ++i)
	{
		DistanciaVec[i] = atm1[i] + atm2[i] ;
		DistanciaVec[i] = sqrt(pow(DistanciaVec[i],2));
		std::cout << atm1[i] << " + " << atm2[i] << " = " << DistanciaVec [i] << std::endl;
	}	
}

void LennardJones(const double Epsilon , const double Sigma, std::vector<double>& Potencial,const std::vector<double> Distancia){


	 Potencial[0]=4*Epsilon*( pow((Sigma/Distancia[0]),12) - pow((Sigma/Distancia[0]),6));
	 //Schroeder, D. V. (2015). Interactive molecular dynamics. American Journal of Physics, 83(3), 210–218.
	
	 std::cout << "El potencial de Lennard Jonnes para los parametros: Epsilon=" << Epsilon << " Sigma=" << Sigma << " r=" << Distancia[0] << "\n";
     std::cout << "Es " << Potencial[0] << std::endl;


}


void FuerzaLJ( const double Epsilon , const double Sigma , const std::vector<double> R , const std::vector<double> DistanciaVec ,std::vector<double>& Fuerza){

	for (size_t i = 0; 3 > i ; ++i)
	{
			Fuerza[i]=abs(4*Epsilon*(12*pow(Sigma,12)/pow(R[0],13) - 6* pow(Sigma,6)/pow(R[0],7))*DistanciaVec[i]);
	}
	//
	std::cout << "La Derivada del Potencial de Lennard Jonnes para los parametros: Epsilon=" << Epsilon << " Sigma = " 
	<< Sigma << " r=" << R[0] << "\n";
        std::cout << "Es " << std::endl;

    for (size_t i = 0; 3 > i ; ++i)
	{
			std::cout << Fuerza[i]	<< std::endl;
	}

}



void PosVerlet( std::vector<double>& PosIn, std::vector<double>& PosFin, std::vector<double>& PosAnt , const std::vector<double> Aceleracion , const double dt ){
	//\vec{x}(t + \Delta t) = 2\vec{x}(t) - \vec{x}(t - \Delta t) + \vec{a}(t) \Delta t^2 + O(\Delta t^4)
	    for (size_t i = 0; 3 > i ; ++i)
		{

			 PosFin[i] = 2*PosIn[i]-PosAnt[i]+Aceleracion[i]*pow(dt,2);

		}
	 //Vzzlzrt, L. (1967). “Exyeriments” on Classical Fluids. I. Thermodynamical Properties of Lennard,-Jones Molecules~.
	 
}

void VelVerlet(std::vector<double>& Velocidad, const std::vector<double> PosFin,const std::vector<double> PosAnt, const double dt){

	//\vec{v}(t) = [ \vec{x}(t + \Delta t) - \vec{x}(t - \Delta t)] / (2 \Delta t)
	for (size_t i = 0; 3 > i ; ++i)
	{
		 Velocidad[i] = (PosFin[i]-PosAnt[i])/(2*dt);
	}
	
	//Vzzlzrt, L. (1967). “Exyeriments” on Classical Fluids. I. Thermodynamical Properties of Lennard,-Jones Molecules~.

	
	for (size_t i = 0; 3 > i ; ++i)
	{
		 std::cout << Velocidad[i] << std::endl;
	}
}




void AceleracionVec(std::vector<double>& Aceleracion,const std::vector<double> VelocidadIn,const std::vector<double> VelocidadFin,const double dt){
	
	Aceleracion={0,0,0};
	//std::cout << "El vector de Aceleracion es " << std::endl;

	for (size_t i = 0; i < 3 ; ++i)
	{
		Aceleracion[i]=(VelocidadIn[i]-VelocidadFin[i])/dt;
		std::cout << Aceleracion[i] << std::endl;
	}
}

/*
void Temperatura(std::vector<double>& Temp,  double Kb, double nat, std::vector<double>& Ekin ){

	Temp = (2/3) * (Ekin/(nat*Kb))

}

*/

void PrimerPaso(std::vector<double>& atm1, std::vector<double>& atm2, std::vector<double>& Distancia, std::vector<double>& DistanciaVec,
			const double Epsilon, const double Sigma, std::vector<double> Potencial,std::vector<double>& Fuerza,
			 std::vector<double>& PosAnt , 
			 std::vector<double>& PosAnt2 ,
			 std::vector<double>& Aceleracion,std::vector<double>& Aceleracion2 , const double dt, const std::vector<double> DimCaja,const std::vector<double> DimCajaMin,
			 std::vector<double>& VelocidadFin, std::vector<double>& VelocidadFin2,
			 std::vector<double>& VelocidadIn, std::vector<double>& VelocidadIn2
			 )
{

		 std::cout << "Para el primer paso:" << std::endl;

		 Distancia3DVec(atm1,atm2,Distancia);

		 std::cout << "La distancia entre los atomos en forma escalar es " << std::endl ;

	 	 std::cout << Distancia[0] << std::endl ;

		 std::cout << "La distancia entre los atomos en forma de vector es " << std::endl ;

	 	 VecSum(atm1,atm2,DistanciaVec);

	 	 LennardJones( Epsilon,  Sigma, Potencial ,  Distancia );

	 	 FuerzaLJ(Epsilon, Sigma, Distancia , DistanciaVec , Fuerza);


	 	 for (int i = 0; i < 3; ++i)
	 	 {

	 	 		 VelocidadFin[i] = ( Fuerza[i] * dt ) + VelocidadIn[i];

	 	 		 VelocidadFin2[i] = (Fuerza[i] * dt ) + VelocidadIn2[i];
	 	 		
	 	 }


	 	 for (int i = 0; i < 3; ++i)
	 	 {
	 	 	PosAnt[i] = atm1[i];

	 	 	PosAnt2[i] = atm2[i];

	 	 }

	 	 for (int i = 0; i < 3; ++i)
	 	 {

	 	 	atm1[i] = atm1[i]+(VelocidadFin[i]*dt);

	 	 	if (atm1[i]  > DimCaja[i])
	 	 	{
	 	 		atm1[i] = DimCajaMin[i] + atm1[i] -DimCaja[i];
	 	 	}

	 	 	if (atm1[i]  < DimCajaMin[i])
	 	 	{
	 	 		atm1[i] = DimCajaMin[i] + abs(atm1[i] + DimCaja[i]);
	 	 	}
	 	 	
	 	 }

	 	 for (int i = 0; i < 3; ++i)
	 	 {

	 	 	atm2[i] = atm2[i]+(VelocidadFin2[i]*dt);

	 	 	if (atm2[i]  > DimCaja[i])
	 	 	{
	 	 		atm2[i] = DimCajaMin[i] + atm2[i] -DimCaja[i];
	 	 	}

	 	 	if (atm2[i]  < DimCajaMin[i])
	 	 	{
	 	 		atm2[i] = DimCajaMin[i] + abs(atm2[i] + DimCaja[i]);
	 	 	}
	 	 	
	 	 }

	 		 	 	

	 	 std::cout << "Las nuevas coordenas del atomo 1 son : " << std::endl;

	 	 for (int i = 0; i < 3; ++i)
	 	 {

	 	 	std::cout << atm1[i] << std::endl;


	 	 }

	 	 std::cout << "Las nuevas coordenas del atomo 2 son : " << std::endl;

	 	 for (int i = 0; i < 3; ++i)
	 	 {

	 	 	std::cout << atm2[i] << std::endl;

	 	 }

	 	 std::cout << "Las velocidades del primer atomo son" << "\n";
	 	 
	 	 for (int i = 0; i < 3; ++i)
	 	 {

	 	 		std::cout << VelocidadFin[i] << std::endl;


	 	 }


		 std::cout << "El vector de Aceleracion es para el atomo 1 es " << std::endl;
		 AceleracionVec(Aceleracion , VelocidadIn, VelocidadFin, dt);



		 std::cout << "Las velocidades del segundo atomo son" << "\n";
	 	 
	 	 for (int i = 0; i < 3; ++i)
	 	 {

	 	 		std::cout << VelocidadFin2[i] << std::endl;

	 	 }


		 std::cout << "El vector de Aceleracion es para el atomo 2 es " << std::endl;
		 AceleracionVec(Aceleracion2 , VelocidadIn2, VelocidadFin2, dt);

		 std::cout << "--------------------Fin paso" << " 1 " << "--------------------------" << std::endl;

	 	 	
}

void Din2Atm(std::vector<double>& atm1, std::vector<double>& atm2, std::vector<double>& Distancia, std::vector<double>& DistanciaVec,
			const double Epsilon, const double Sigma, std::vector<double> Potencial,std::vector<double>& Fuerza,
			 std::vector<double>& PosFin, std::vector<double>& PosAnt , 
			 std::vector<double>& PosFin2, std::vector<double>& PosAnt2 ,
			 std::vector<double>& Aceleracion,std::vector<double>& Aceleracion2 , const double dt, const std::vector<double> DimCaja,const std::vector<double> DimCajaMin,
			 std::vector<double>& VelocidadFin, std::vector<double>& VelocidadFin2,
			 std::vector<double>& VelocidadIn, std::vector<double>& VelocidadIn2,const size_t npas
			 )
{

for (size_t i = 0; i < npas-1; ++i)
	{

		 Distancia3DVec(atm1,atm2,Distancia);

		 std::cout << "La distancia entre los atomos en forma escalar es " << std::endl ;

	 	 std::cout << Distancia[0] << std::endl ;

		 std::cout << "La distancia entre los atomos en forma de vector es " << std::endl ;

	 	 VecSum(atm1,atm2,DistanciaVec);

	 	 LennardJones( Epsilon,  Sigma, Potencial ,  Distancia );

	 	 FuerzaLJ(Epsilon, Sigma, Distancia , DistanciaVec , Fuerza);


		 PosVerlet( atm1, PosFin, PosAnt , Aceleracion , dt  );

	 	 std::cout << "Las nuevas coordenadas del atomo 1 son" << std::endl ;

	  	 for (size_t i = 0; 3 > i ; ++i)
	 	 {

			 std::cout << PosFin[i] << std::endl ;

	 	 }

	 	 PosVerlet( atm2, PosFin2, PosAnt2 , Aceleracion2 , dt  );

	 	 std::cout << "Las nuevas coordenadas del atomo 2 son" << std::endl ;

	 	 for (size_t i = 0; 3 > i ; ++i)
	  	 {

		 std::cout << PosFin2[i] << std::endl ;

	 	 }

		 std::cout << "Las velocidad del primer atomo según el algoritmo de Verlet es" << "\n";

	 	 VelVerlet(VelocidadFin, PosFin, PosAnt, dt);
		 std::cout << "El vector de Aceleracion es para el atomo 1 es " << std::endl;
	 	 AceleracionVec(Aceleracion, VelocidadIn, VelocidadFin, dt);

	 	 std::cout << "Las velocidad del segundo atomo según el algoritmo de Verlet es" << "\n";
	 	 VelVerlet(VelocidadFin2, PosFin2, PosAnt2, dt);
		 std::cout << "El vector de Aceleracion es para el atomo 2 es " << std::endl;
	 	 AceleracionVec( Aceleracion2 , VelocidadIn2, VelocidadFin2, dt);

		for (size_t i = 0; i < 3; ++i)
			{

				PosAnt[i]=atm1[i];
				atm1[i]=PosFin[i];

				//Condiciones periodicas!!!

	 	 		if (PosFin[i]  > DimCaja[i])
	 	 		{
	 	 			PosFin[i] = DimCajaMin[i] + PosFin[i] - DimCaja[i];
					PosAnt[i] = DimCajaMin[i] + PosAnt[i] - DimCaja[i];
					atm1[i] = DimCajaMin[i] + atm1[i] - DimCaja[i];
	 	 		}

	 	 		if (PosFin[i]  < DimCajaMin[i])
	 	 		{
	 	 			PosFin[i] = DimCaja[i] - abs(PosFin[i] - DimCajaMin[i] );
	 	 			PosAnt[i] = DimCaja[i] - abs(PosAnt[i] - DimCajaMin[i] );
					atm1[i] = DimCaja[i] - abs(atm1[i] - DimCajaMin[i] );
	 	 		}

	 	 		if (PosFin2[i]  > DimCaja[i])
	 	 		{
	 	 			PosFin2[i] = DimCajaMin[i] + PosFin2[i] - DimCaja[i];
					PosAnt2[i] = DimCajaMin[i] + PosAnt2[i] - DimCaja[i];
					atm2[i] = DimCajaMin[i] + atm2[i] - DimCaja[i];
	 	 		}

	 	 		if (PosFin2[i]  < DimCajaMin[i])
	 	 		{
	 	 			PosFin2[i] = DimCaja[i] - abs(PosFin2[i] - DimCajaMin[i] );
	 	 			PosAnt2[i] = DimCaja[i] - abs(PosAnt2[i] - DimCajaMin[i] );
	 	 			atm2[i] = DimCaja[i] - abs(atm2[i] - DimCajaMin[i] );
	 	 		}

			

			}
			std::cout << "--------------------Fin paso  " << i+2 << "--------------------------" << std::endl;
	 }

}


void Dinamica(std::vector<double> atm1 , std::vector<double> atm2 , std::vector<double> VelocidadIn,std::vector<double> VelocidadIn2, 
			const std::vector<double> DimCaja, const std::vector<double> DimCajaMin, const double EpsAr , const double SigmaAr,
			const double Npas, const double dt){

	// White, J. A. (1999). Lennard-Jones as a model for argon and test of extended renormalization group calculations

	
	//Inicializadores
	 std::vector<double> Aceleracion{0,0,0} ;
	 std::vector<double> Aceleracion2{0,0,0} ;
	 std::vector<double> PosAnt{0,0,0};
	 std::vector<double> PosFin{0,0,0};
	 std::vector<double> PosAnt2{0,0,0};
	 std::vector<double> PosFin2{0,0,0};
	 std::vector<double> DistanciaVec{0,0,0} ;
	 std::vector<double> Distancia{0};
	 std::vector<double> Potencial{0} ;
	 std::vector<double> Fuerza{0,0,0} ;
	 std::vector<double> VelocidadFin{0,0,0} ;
	 std::vector<double> VelocidadFin2{0,0,0} ;


	 PrimerPaso(atm1, atm2, Distancia, DistanciaVec,
	 		 EpsAr,SigmaAr,Potencial,Fuerza,
	 		 PosAnt , 
	 		 PosAnt2 ,
			 Aceleracion , Aceleracion2 , dt, DimCaja,DimCajaMin,
			 VelocidadFin, VelocidadFin2,
			 VelocidadIn, VelocidadIn2);

	 
	 Din2Atm(atm1, atm2, Distancia, DistanciaVec,
	 		 EpsAr,SigmaAr,Potencial,Fuerza,
	 		 PosFin, PosAnt , 
	 		 PosFin2, PosAnt2 ,
			 Aceleracion , Aceleracion2 , dt, DimCaja, DimCajaMin,
			 VelocidadFin, VelocidadFin2,
			 VelocidadIn, VelocidadIn2,Npas);
}

