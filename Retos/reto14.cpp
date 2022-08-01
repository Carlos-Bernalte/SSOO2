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
#include <mutex>
#include <condition_variable>

//RETO ANULADO
#define N 5
int nPalillos=2;
std::condition_variable palillos;
std::mutex acceso;
std::mutex sem_filosofo;
std::vector<std::thread> comensales;

void filosofo(int i){
    //std::cout<<"El comensal "<< i <<" creado."<<std::endl;
    
    while(1){
        
        //pensando
        std::cout<<"El comensal "<< i <<" esta pensando. Número de palillos: "<<nPalillos<< std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));


        //comiendo
        std::unique_lock<std::mutex> ulF(sem_filosofo);
        palillos.wait(ulF, []{
            return nPalillos>0;
        });
        ulF.unlock();

        acceso.lock();
        nPalillos--;
        acceso.unlock();

        std::cout<<"El comensal "<< i <<" esta comiendo. Número de palillos: "<<nPalillos<< std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        acceso.lock();
        nPalillos++;
        acceso.unlock();
        palillos.notify_one();
        
    }
}
int main(int argc, char *argv[]){
    for (int i = 0; i < 5; i++) {
        comensales.push_back(std::thread(filosofo, i));  
    }
    std::for_each(comensales.begin(), comensales.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}