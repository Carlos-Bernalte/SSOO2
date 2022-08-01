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
#include "SemCounter2.cpp"

#define N 5

std::condition_variable full;
std::condition_variable empty;
std::mutex acceso;
std::mutex semProductor;
std::mutex semConsumidor;
std::vector<int> mi_buffer;
std::vector<std::thread> vHilos;


void productor(int i){
    std::unique_lock<std::mutex> ulP(semProductor);
    while(1){
       empty.wait(ulP,[]{
           return mi_buffer.size()<5;
       });
       acceso.lock();
       mi_buffer.push_back(1);
       std::cout <<"["<< i <<"] Productor: "<< mi_buffer.size() << std::endl;
       acceso.unlock();
       full.notify_one();
       std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void consumidor(int i){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::unique_lock<std::mutex> ulC(semConsumidor);
    while(1){
        full.wait(ulC,[]{
            return mi_buffer.size()>0;
       });
        acceso.lock();
        mi_buffer.pop_back();
        std::cout <<"["<< i <<"] Consumidor: "<< mi_buffer.size() << std::endl;
        acceso.unlock();
        empty.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
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