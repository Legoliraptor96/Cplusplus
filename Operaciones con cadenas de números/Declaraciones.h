#ifndef DECLARACIONESEXAMEN_H
#define DECLARACIONESEXAMEN_H

//FUNCION PARA IMPRIMIR UN VECTOR
void PrintVector(std::vector<int>& );

//FUNCION PARA IMPRIMIR UNA CADENA
void PrintStrint(std::vector<std::string> );


//FUNCION PARA HACER EL DOBLE DE LOS PARES
void VecDob(std::vector<int>& );

//FUNCION QUE SUMA DOS DIGITOS DE UN NUMERO ENTERO
int SumaDigitos(int , int& );

//FUNCION QUE SUMA LOS DOS DIGITOS DE UN NUMERO ENTERO CONTENIDOS EN UN VECTOR
int SumaDigitosVec(std::vector<int>& );

//FUNCION QUE SUMA LOS ELEMENTOS DE UN VECTOR
int SumaVectorTot(std::vector<int> , int& );

//FUNCION QUE HACE TODO LO QUE PIDE EL EXAMEN PARA UN VECTOR DADO :)
void ProgramaGlobal(std::vector<int> );

//FUNCION QUE LEE EL ARCHIVO DADO
void LeerArchivo(std::string ,std::vector<std::string>& );

//FUNCION QUE HACE LO QUE PIDE EL EXAMEN EN UNA MATRIZ
void ProgramaGlobalMatriz(std::vector<std::vector<int>> v);

#endif