#ifndef LECTURA_H
#define LECTURA_H

void parametros(char **argv, int& nAtom, double& boxSize,
                double& temp, double& time, int& nPaso, bool& termostat){
                  
    std::string outFile;
                  
    nAtom = std::atoi(argv[2]);
    temp = std::atof(argv[3]);
    time = std::atof(argv[4]);
    nPaso = std::atoi(argv[5]);
    boxSize = std::atof(argv[6]);
                  
    std::cout << "El título de la simulación es "
              << argv[1] << "\n" ;
                  
    std::cout << "Participan  " << nAtom
              << " átomos " << "\n" ;
                  
    std::cout << "La caja tiene un tamaño de " << boxSize
              << "A por lado " << "\n" ;
                  
    std::cout << "Hay una temperatura de "
              << temp << " K " << "\n" ;
                                        
    std::cout << "Cada paso tiene una duración de "
              << time << " picosegundos " << "\n" ;
                  
    std::cout << "Son " << nPaso << " pasos " << "\n" ;
                  
    if (std::atoi(argv[7]) == 0)
         termostat = 1 ; 
               
    termostat ?
    std::cout << "Vamos a usar el termostat" :
    std::cout << "No vamos a usar el termostat" ;
    std::cout << std::endl ;
}

#endif
