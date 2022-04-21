#include <iostream>
#include <vector>
#include "DeclaracionesExamen.h"


int main(int argc, char **argv){

	std::vector<int> num1{2,0,9,8,6,7,3};

	std::vector<std::vector<int>> v{{2,0,9,8,6,7,3},{1,7,6,2,4,8,3},{1,6,9,1,3,5,1},{6,0,8,1,9,3,8}};

	//ProgramaGlobal(num1);

	//este es elejemplo que muestra que si lograba leer la matriz mi programa podia hacer todo lo que pediamos para lso diferentes vectores
	ProgramaGlobalMatriz(v);

	std::vector<std::string> Vector;

	LeerArchivo(argv[1],Vector);

	PrintStrint(Vector);



	//La idea aqui era pasar el std::vector<std::string> Vector a std::vector<std::vector<int>> y
	// por que mi progrmaa es capaz de leer matrices pero no cadenas

	std::vector<std::vector<int>> y;

	y={};

	for(int j = 1; j < 4 ; ++j){
		for (int i = 0; i < 7; ++i)
		{
				
				//y[j][i] += Vector[j][i];

				std::cout << Vector[j][i] << std::endl;

		}
	}

	//aunque logre identificar los valores de la matriz dada no pude guardarlos en una matriz, se que es un error tonto pero 
	//no se me ocurrio como
}
