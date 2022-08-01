#include <iostream>
#include <thread>
#include <chrono>

void funcion(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //dormir durante 1 seg
    std::cout << "Funcion finalizada" <<std::endl;
}

int main(){
    std::thread f (funcion);
    f.join(); //Con esta opcion ambos procesos acaban, 
    //f.detach(); //Con esta solo se visualiza la terminacion del main
    std::cout << "Main finalizada" <<std::endl;
}