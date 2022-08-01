#include <iostream>
#include <cctype>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <future>

void A(std::promise<int> prom, std::future<int>& fut){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    prom.set_value(10);
    std::cout<<"Proceso A bloqueado"<<std::endl;
    int x=fut.get();
    std::cout<<"Proceso A desbloqueado"<<std::endl;
}

void B(std::promise<int> prom, std::future<int>& fut){
    std::cout<<"Proceso B bloqueado"<<std::endl;
    fut.get();
    std::cout<<"Proceso B desbloqueado"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    prom.set_value(10);
}

int main(int argc, char *argv[]){
    std::promise<int> promA;
    std::promise<int> promB;

    std::future<int> futA = promA.get_future();
    std::future<int> futB = promB.get_future();

    std::thread th1 (A, promA, std::ref(futB));
    std::thread th2 (B, promB, std::ref(futA));

    th1.join();
    th2.join();

    return EXIT_SUCCESS;
}