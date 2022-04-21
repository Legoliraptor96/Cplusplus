#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>

//FUNCION QUE LEE EL ARCHIVO DADO
void LeerArchivo(std::string archivo1,std::vector<std::string>& Vector){

	std::ifstream iFile {archivo1};

	if(iFile){

			std::string Linea;

			while (std::getline(iFile, Linea)){   

				Vector.push_back(Linea); 

			}   
    }

}


//FUNCION PARA IMPRIMIR UN VECTOR
void PrintVector(std::vector<int>& a){
	for (size_t i = 0;  a.size() > i; ++i)
	 {
	 	std::cout << a[i] << std::endl;
	 }
}

//FUNCION PARA IMPRIMIR UNA CADENA
void PrintStrint(std::vector<std::string> a){

	size_t tam = a.size();

	for (size_t i = 0; i < tam ; ++i)
	{
		std::cout << a[i] << std::endl;
	}

}

//FUNCION PARA HACER EL DOBLE DE LOS PARES
void VecDob(std::vector<int>& a){

	//doblar pares

	size_t tam;

	tam = a.size();

	for (size_t i = 0; i < tam ; ++i)
	{
		if (i % 2 == 0 )
		{
			a[i] = a[i];
		}

		else{
			a[i] += a[i];
		}

	}
}

//FUNCION QUE SUMA DOS DIGITOS DE UN NUMERO ENTERO
int SumaDigitos(int n, int& suma) {

   suma=0;

   if (n < 0) n=-n;
   
   while (n!=0) {

     suma+=n%10;            

      n=n/10;               

   }

   return suma;
}

//FUNCION QUE SUMA LOS DOS DIGITOS DE UN NUMERO ENTERO CONTENIDOS EN UN VECTOR
int SumaDigitosVec(std::vector<int>& a){
	
	size_t tam;

	tam = a.size();

	for (size_t i = 0; i < tam; ++i)
	{
		  a[i] = SumaDigitos(a[i],a[i]);
	}
}


//FUNCION QUE SUMA LOS ELEMENTOS DE UN VECTO
int SumaVectorTot(std::vector<int> a, int& suma){
	
	size_t tam;

	tam = a.size();

	suma=0;

	for (size_t i = 0; i < tam; ++i)
	{
		  suma += a[i];
	}
}

//FUNCION QUE HACE TODO  PARA UN VECTOR DADO :)
void ProgramaGlobal(std::vector<int> num1){

	std::cout << " Para el Vector " << std::endl;

	PrintVector(num1);

	VecDob(num1);

	SumaDigitosVec(num1);

	//PrintVector(num1);

	int Suma;

	SumaVectorTot(num1,Suma);

	//std::cout << Suma << std::endl;

	if (Suma % 10 == 0)
	{
		std::cout	<< "el número es " << Suma << " y es valido" << std::endl;
	}
	else{
		std::cout	<< "el número es " << Suma << " y no es valido" << std::endl;
	}

}

//FUNCION QUE HACE LO QUE PIDE EL EXAMEN EN UNA MATRIZ
void ProgramaGlobalMatriz(std::vector<std::vector<int>> v){

	size_t Col, Ren;
    Col=v[0].size();
    Ren=v.size();

    for (size_t i = 0; i < Ren ; ++i)
    {
    		ProgramaGlobal(v[i]);
    }

}