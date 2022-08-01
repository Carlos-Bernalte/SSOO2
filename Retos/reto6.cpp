#include <iostream>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <vector>
#include <thread>
#include <functional>
#include <stdlib.h>
#include <string.h>
#include <atomic>
#define LIMITE 400

long suma=0;
std::vector<int> numeros;

void sumar(int inicio, int final){
    
    for(int i=inicio; i<final; i++){
        suma=suma+numeros[i];
    }
    
}

int main(int argc, char *argv[]){
    int nHilos = std::thread::hardware_concurrency();
    std::cout << "Numero de hilos: "<<std::to_string(nHilos) << std::endl;
    std::vector<std::thread> hilos;
    srand(time(NULL));

    int x = LIMITE/nHilos;
    int inicio=0;
    int final=x;

    unsigned t0, t1;
    
    t0=clock();

    for (int i = 0; i < LIMITE; i++)
    {
        numeros.push_back(rand());
    }
    
    for (int i = 0; i < nHilos; i++) {
        hilos.push_back(std::thread(sumar, inicio, final));
        inicio=final;
        final=inicio+x;
    }
    
    std::for_each(hilos.begin(), hilos.end(), std::mem_fn(&std::thread::join));
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    std::cout << "Suma final: "<< std::to_string(suma)<< std::endl;
    std::cout << "Tiempo de ejecución: " << time << std::endl;
    return EXIT_SUCCESS;
}