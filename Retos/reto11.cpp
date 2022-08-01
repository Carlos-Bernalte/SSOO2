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

std::mutex sem;
std::vector<std::thread> hilos;
int turno;

void hilo(int i){
    while (turno!=i)
    {   
    }
    std::cout<<"Es mi turno "<< i << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    sem.unlock();
    
}

int main(int argc, char *argv[]){
    for (int i = 0; i < 10; i++) {
        hilos.push_back(std::thread(hilo, i));  
    }
    sem.lock();
    for (int i = 0; i < 10; i++) {
        turno=i;
        sem.lock(); 
    }
    std::for_each(hilos.begin(), hilos.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}