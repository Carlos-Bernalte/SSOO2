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
    int getValue(){
        return this->x;
    }

};

int main(){
    Reto r;

    std::cout << "Valor de x "<< r.x <<std::endl;
    std::thread hilo(std::ref (r));
    hilo.join();
    std::cout << "Valor de x "<< r.x <<std::endl;
    return 0;
}