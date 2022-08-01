#ifndef QUEU
#define QUEU

#include <queue>
#include <mutex>
#include <future>
#include "Request.cpp"

/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: QueueProtected.cpp
*
*   Author: Carlos Bernalte García-Junco & Paulino De La Fuente Lizcano
*
*   Date created: 24-03-2021
*
*   Porpuse: Cola para almacenar y manejar las peticiones de pago 
*
*   Revision History: Se puede encontrar en el repositorio de GitHub.
|*********************************************/

class QueueProtected
{
private:
    std::mutex access;
    
public:
    std::queue<Request> queueRequest;
    QueueProtected();
    void add(Request r);
    Request remove();
    bool checkEmpty();
};

QueueProtected::QueueProtected()
{
}

/*Metodo para verificar que la cola no este vacía*/
bool QueueProtected::checkEmpty(){
    std::unique_lock<std::mutex> ul(access);
    return this->queueRequest.empty();
    
}
/*Metodo para almacenar peticiones referenciadas en la cola*/
void QueueProtected::add(Request r){
    std::unique_lock<std::mutex> ul(access);
    this->queueRequest.push(std::move(r)); 
}
/*Metodo que devuelve la primera peticón de la cola y la elimina de ella*/
Request QueueProtected::remove(){
    std::unique_lock<std::mutex> ul(access);
    Request r = std::move(this->queueRequest.front());
    this->queueRequest.pop();
    return r;
}
#endif
