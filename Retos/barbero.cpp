#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <functional>
#include <atomic>
#include <mutex>
#include <unistd.h>
#include <bits/stdc++.h>

/*Vector donde cada posicion representa un semaforo, los cuales representan los palillos*/

/*Semaforo para limitar el acceso a la mesa de los comensales*/
std::mutex despertar_barbero;
std::mutex mtx_clientes;
std::mutex terminar_corte;
std::mutex sillon_barbero;
/*Representa las sillas libres dentro de la barberia*/
#define N 3
int num_clientes=0;


void barbero(){
    
    while(1){
        despertar_barbero.lock();
        std::cout<<"[Barbero] Cortando pelo a cliente "<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        terminar_corte.unlock();
    }
}

void cliente(int id){
    mtx_clientes.lock();
    std::cout<<"[Cliente "<<id<<"]"<<"He llegado"<<std::endl;
    if(num_clientes==N){
        mtx_clientes.unlock();
        std::cout<<"[Cliente "<<id<<"]"<<"abandona la barberia"<<std::endl;
        return;
    }
    num_clientes++;
    std::cout<<"[Cliente "<<id<<"]"<<"Sala de espera"<<std::endl;
    mtx_clientes.unlock();
        
        /*Tomamos el asiento*/
    sillon_barbero.lock();
        /*Protegemos la variable de control del numero de clientes*/
        mtx_clientes.lock();
            num_clientes--;
        mtx_clientes.unlock();
        /*Despertamos al barbero y esperamos a que nos corte el pelo*/
        despertar_barbero.unlock();
        terminar_corte.lock();
        std::cout<<"[Cliente "<<id<<"]"<<"satisfecho"<<std::endl;
    sillon_barbero.unlock();
    }

int main(int argc, char *argv[]){

    std::vector<std::thread>vhilos;

    vhilos.push_back(std::thread (barbero));

    for(int i=0;i<10;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        vhilos.push_back(std::thread(cliente,i));
    }

    std::for_each(vhilos.begin(), vhilos.end(), std::mem_fn(&std::thread::join));
    return 0;
}
