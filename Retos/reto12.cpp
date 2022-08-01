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

std::mutex sem;
std::mutex sem2;

std::condition_variable cv;
std::vector<std::thread> hilos;
int turno;

void hilo(int id){
    std::unique_lock<std::mutex> ul(sem2);
    cv.wait(ul,[id]{
        if(id==turno){
            return true;
        }else{
            return false;
        }
    });
    std::cout<<"Es mi turno "<< id << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); 
    sem.unlock();
    
}

int main(int argc, char *argv[]){
    turno=-1;
    for (int i = 0; i < 10; i++) {
        hilos.push_back(std::thread(hilo, i)); 
    }
    sem.lock();
    for (int i = 0; i < 10; i++) {
        turno=i;
        cv.notify_all();
        sem.lock(); 
    }
    std::for_each(hilos.begin(), hilos.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}