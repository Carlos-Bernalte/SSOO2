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
#define LIMITE 4

std::atomic<long> suma (0);
std::vector<int> numeros;

void sumar(int inicio, int final){
    
    for(int i=inicio; i<=final; i++){
        suma+=numeros[i];
    }
    
}

int main(int argc, char *argv[]){
    int nHilos = std::thread::hardware_concurrency();

    std::vector<std::thread> hilos;
    
    long sumaSinHilos=0;
    srand(time(NULL));

    int x = LIMITE/nHilos;
    int inicio=0;
    int final=x;

    unsigned t0, t1;
    
    t0=clock();

    for (int i = 0; i < LIMITE; i++)
    {
        numeros.push_back(rand());
        sumaSinHilos+=numeros[i];
    }
    
    for (int i = 0; i < nHilos; i++) {
        inicio=i*x;
        final=(inicio+x)-1;
        hilos.push_back(std::thread(sumar, inicio, final));  
    }
    
    std::for_each(hilos.begin(), hilos.end(), std::mem_fn(&std::thread::join));
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    std::cout << "Suma final sin hilos: "<< std::to_string(sumaSinHilos)<< std::endl;
    std::cout << "Suma final con hilos: "<< std::to_string(suma)<< std::endl;
    std::cout << "Tiempo de ejecución: " << time << std::endl;
    return EXIT_SUCCESS;
}