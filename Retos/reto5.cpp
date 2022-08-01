#include <iostream>
#include <stdlib.h>
#include <thread>

class Reto
{
    
public:
    int x;
    Reto(){
        this->x=3;
    }
    void operator () (){
        this->x=7;
    } 

};

int main(){
    Reto r;

    std::cout << "Valor de x "<< r.x <<std::endl;
    std::thread hilo(r);
    hilo.join();
    std::cout << "Valor de x "<< r.x <<std::endl;
    return 0;
}