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

SemCounter counter(3);
std::vector<std::thread> hilos;

void hilo(int i){
    while (1)
    {
        counter.wait();
        std::cout<<"Hola soy el hilo"<< i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        counter.signal();
    }
    
}

int main(int argc, char *argv[]){
    for (int i = 0; i < 10; i++) {
        hilos.push_back(std::thread(hilo, i));  
    }
    std::for_each(hilos.begin(), hilos.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}