/*
El siguiente programa fue implementado en Ubuntu 18.04 LTS.
Nota: al ejecutar el programa por primera vez en Qt obtuve errores como
"undefined reference to pthread_create" por lo que tuve que agregar lo siguiente al .pro:
LIBS += -pthread
-----------------------------------------------------------------------------------------
El siguiente programa utiliza  múltiples hilos para ejecutar dos funciones:
la primera función se encarga de duplicar un número que se le pasa por referencia y la segunda
función se encarga de sumar dos números que se le pasan como parámetros.
Además, los hilos que ejecuten la función 1 deberán dormir durante 10 segundos después de
realizar la multiplicación, mientras que el hilo que ejecuta la función 2 deberá dormir por
3 segundos antes de realizar la suma.
Por último, se mostrarán los tiempos de inicio y finalización de la ejecución de cada función.
*/
#include <iostream>
//librería para manejo de hilos a partir de C++11:
#include<thread>
//librerías utilizada para definir un tiempo de espera en la ejecución de los hilos e imprimir
//tiempo de inicio y finalización de cada hilo:
#include<chrono>
#include<ctime>
//Librería que permite sincronizar los hilos:
#include<mutex>
using namespace std;
mutex candado; //declaración para uso de clase mutex.
void Funcion1(int &n, int ID){
    /*
     Función que recibe como parámetros una identificación de hilo y un número por referencia.
     Imprime la identificación y el número duplicado, así como los tiempos de inicio y finalización
     de la ejecución.
    */
    //Bloqueando el acceso de otros hilos a la función hasta que el hilo actual
    //termine de ejecutarla. Si no se colocara este método de la clase mutex, ambos
    //hilos podrían ejecutar la función simultáneamente.
    candado.lock();
    auto start = std::chrono::system_clock::now(); //Obteniendo tiempo de inicio
    n*=2;
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Lo siguiente fue realizado por el hilo "<<ID<<": "<<endl;
    //Obtenemos el ID propio del hilo para confirmar que realmente se están ejecutando
    //hilos diferentes:
    cout<<"ID: "<<this_thread::get_id()<<endl;
    cout<<"Resultado: "<<n<<endl;
    auto end = chrono::system_clock::now();
    time_t fin = chrono::system_clock::to_time_t(end);
    time_t inicio = chrono::system_clock::to_time_t(start);
    cout<<"Inicio ejecucion: "<<ctime(&inicio)<<endl;
    cout<<"Fin ejecucion: "<<ctime(&fin)<<endl;
    this_thread::sleep_for(chrono::seconds(10)); //haciendo que el hilo duerma por 10 segundos
    cout<<"Ejecucion completada..."<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    candado.unlock(); //Desbloqueando la función para que la ejecute el siguiente hilo.

}
void Funcion2(int i, int j, int ID){
    /*
     Función que recibe como parámetros tres números enteros que corresponden a dos números
     que se sumarán y una identificación del hilo actual.
     Imprime el ID del hilo así como el resultado de la suma de los dos primeros parámetros.
    */
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Esperando 3 segundos..."<<endl;
    this_thread::sleep_for(chrono::seconds(3)); //haciendo que el hilo duerma por 3 segundos
    auto start = std::chrono::system_clock::now();
    cout<<"Lo siguiente fue realizado por el hilo "<<ID<<": "<<endl;
    cout<<"ID: "<<this_thread::get_id()<<endl;
    cout<<"Resultado: "<<i+j<<endl;
    auto end = chrono::system_clock::now();
    time_t fin = chrono::system_clock::to_time_t(end);
    time_t inicio = chrono::system_clock::to_time_t(start);
    cout<<"Inicio ejecucion: "<<ctime(&inicio)<<endl;
    cout<<"Fin ejecucion: "<<ctime(&fin)<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
}
int main()
{
    int compartido=8;
    thread hilo1(Funcion1,ref(compartido),1); //forma como se pasan variables por referencia
    thread hilo2(Funcion1,ref(compartido),2);
    hilo1.join();
    hilo2.join(); //Se unen los hilos al main
    thread hilo3(Funcion2,7,8,3);
    hilo3.join();
    cout<<"Retorno al main:"<<endl;
    cout<<"ID del hilo: "<<this_thread::get_id()<<endl;
    cout<<"Ha concluido el proceso"<<endl;
}
