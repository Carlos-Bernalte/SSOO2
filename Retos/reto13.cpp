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
#include "SemCounter2.cpp"

#define N 5

SemCounter full(0);
SemCounter empty(N);
std::mutex acceso;
std::vector<int> mi_buffer;
std::vector<std::thread> vHilos;


void productor(int i){
    while(1){
       empty.wait();
       acceso.lock();
       mi_buffer.push_back(1);
       std::cout << "Productor: "<< mi_buffer.size() << std::endl;
       acceso.unlock();
       full.signal();
    }
}

void consumidor(int i){
    
    while(1){
        std::this_thread::sleep_for(std::chrono::seconds(1));
       full.wait();
       acceso.lock();
       mi_buffer.pop_back();
       std::cout << "Consumidor: "<< mi_buffer.size() << std::endl;
       acceso.unlock();
       empty.signal();
    }
}

int main(int argc, char *argv[]){
    for (int i = 0; i < 10; i++) {
        if(i%2==0){
            vHilos.push_back(std::thread(productor, i)); 
        }else{
            vHilos.push_back(std::thread(consumidor, i)); 
        }  
    }

    std::for_each(vHilos.begin(), vHilos.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}