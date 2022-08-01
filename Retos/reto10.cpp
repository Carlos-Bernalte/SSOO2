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


#define N 5

std::mutex palillos[N];
std::vector<std::thread> comensales;

void filosofo(int i){
    while(1){
        //pensar
        std::cout<<"El comensal "<< i <<" esta pensando"<< std::endl;
        palillos[i].lock();
        palillos[(i+1)%5].lock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        //comer
        std::cout<<"El comensal "<< i <<" esta comiendo"<< std::endl;
        palillos[i].unlock();
        palillos[(i+1)%5].unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}
int main(int argc, char *argv[]){
    std::chrono::seconds(5);
    for (int i = 0; i < N; i++) {
        comensales.push_back(std::thread(filosofo, i));  
    }
    std::for_each(comensales.begin(), comensales.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}