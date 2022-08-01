#include <iostream>
#include <stdlib.h>
#include <thread>

class SP{    
public:
  SP(int value);  


};
SP r;

int main(){

    std::cout << "Valor de x "<< r.x <<std::endl;
    std::thread hilo(std::ref (r));
    hilo.join();
    std::cout << "Valor de x "<< r.x <<std::endl;
    return 0;
}