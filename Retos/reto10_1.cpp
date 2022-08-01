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

SemCounter counter(N);
std::mutex palillos[N];
std::vector<std::thread> comensales;

void filosofo(int i){
    while(1){
        //pensar
        counter.wait();
        std::cout<<"El comensal "<< i <<" esta pensando "<< counter.getValue()<<std::endl;
        palillos[i].lock();
        palillos[(i+1)%N].lock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        //comer
        std::cout<<"El comensal "<< i <<" esta comiendo"<< std::endl;
        palillos[i].unlock();
        palillos[(i+1)%N].unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        counter.signal();
    }
}

int main(int argc, char *argv[]){
    for (int i = 0; i < 10; i++) {
        comensales.push_back(std::thread(filosofo, i));  
    }
    std::for_each(comensales.begin(), comensales.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}