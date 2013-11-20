#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "List.h"
#include "AList.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

class Laberinto{
public:
    AList<int> * nodo;  // Puntero a arreglo de listas de arreglos
    int *visitado; // Puntero a arreglo
    int aristas=0;
    int cantNodos=0;
    int visitas = 1;

    // Metodo que inicializa los atributos de la clase
    void init(int cant){
        this->nodo = new AList<int> [cant];
        this->visitado = new int[cant];
        this->cantNodos = cant;
        // Establece que ningun nodo ha sido visitado.
        for(int i=0;i<cant;i++){
            visitado[i]=0;
            nodo[i].clear();
        }
    }

public:
    ~Laberinto(){
        this->limpiarGrafo();
    }
    // Entradas: cantidad de nodos del grafo.
    Laberinto(int cant){
        init(cant);
    }

    // Obtener la cantidad de nodos.
    int getCantidadNodos(){
        return cantNodos;
    }

    // Regresa 0 si un nodo no ha sido visitado
    // 1 si ya fue visitado
    // Entradas: numero de nodo a consultar.
    int isVisitado(int numNodo){
        return this->visitado[numNodo];
    }

    // Establece un nodo como visitado.
    // Entradas: numero de nodo por visitar.
    void setVisitado(int numNodo){
        this->visitado[numNodo] = 1;
    }

    // Devuelve la cantidad de vecinos de un nodo
    // Entrada: numero de nodo que se desea obtener lista de vecinos.
    int getCantVecinos(int numNodo){
        return this->nodo[numNodo].length();
    }

    // Establece una arista entre dos nodos a y b
    // Entradas: nodo a y nodo b
    void setArista(int a, int b){
        this->nodo[a].append(b);
        this->nodo[b].append(a);
        this->aristas += 1;
    }

    // Establece una arista de un punto a otro.
    // Entradas: nodo a y nodo b
    void setAristaIndividual(int a, int b){
        this->nodo[a].append(b);
        this->aristas += 1;
    }

    // Devuelve la cantidad de aristas del grafo
    int getCantAristas(){
        return this->aristas;
    }

    // Devuelve el valor de un vecino aleatorio de un nodo.
    // Entradas: numero de nodo del que se desea obtener un vecino aleatorio.
    int getVecinoAleatorio(int numNodo){
        int cant = this->getCantVecinos(numNodo);
        int aleatorio = rand() % cant;
        this->nodo[numNodo].moveToPos(aleatorio);
        return this->nodo[numNodo].getValue();
    }

    // Devuelve la lista de vecinos de un nodo en el grafo.
    // Entradas: numero de nodo del que se desea obtener lista de vecinos.
    AList<int> getListaVecinos(int numNodo){
        AList<int> temporal(4);
        for (nodo[numNodo].moveToStart();nodo[numNodo].currPos()<nodo[numNodo].length();nodo[numNodo].next()){
            temporal.append(nodo[numNodo].getValue());
        }
        return temporal;
    }

    // Metodo para crear un grafo lleno con todas las aristas.
    void crearTodasAristas(){
        // Filas
        // Se definen los vecinos izquiedo y derecho de un nodo.
        for (int i=0; i <20;i++){
            for (int j=0; j<29; j++){
                this->setArista( j+(i*30), j+(i*30)+1 );
            }
        }
        // Columnas
        // Se definen los vecinos de arriba y abajo de un nodo.
        for (int i=0; i < 30;i++){
            for (int j=i; j<570; j+=30){
                this->setArista( j, j+30 );
            }
        }
    }

    // Metodo para generar el algoritmo de profundidad en el grafo.
    // Entradas: Laberinto lleno, y el numero de nodo donde se desea iniciar el algoritmo.
    void profundidad(Laberinto G,int numNodo){
        this->setVisitado(numNodo);
        AList<int> vecinos = G.getListaVecinos(numNodo);
        vecinos.shuffle(); // Se revuelven los vecinos y se recorren en orden ascendente.
        for (vecinos.moveToStart(); vecinos.currPos()<vecinos.length() ; vecinos.next()){
            if ( (this->isVisitado(vecinos.getValue())) == 0 ) {
                this->setAristaIndividual(numNodo,vecinos.getValue());
                visitas ++;
                profundidad(G,vecinos.getValue());
            }
        }
    }

    //funcion recursiva para recibir un puntero a un arreglo y un numero
    //este recorre el valor indexado del arreglo y el numero
    //yendo a la posicion que tenga el valor del arreglo en con ese numero de indice
    //se detiene cuando llega al valor 0 poruq el arreglo se recorre "para atras"

    //esta funcion gera otro grafo que se utiliza para dibujar la solucion.
    void recorrido(int *ruta,int nodo){
        if (ruta[nodo]==0){
                this->setArista(nodo,ruta[nodo]);
                return;
        }
        this->setArista(nodo,ruta[nodo]);
        recorrido(ruta,ruta[nodo]);
    }

//Fucion para crear la ruta mas corta segun el peso de las aristas
//se inciailizan todos los pesos en 10000
//se pone el primero como visitado y se inicia con peso 0
//se recorren los vecinos se ponen como peso actual +1
//se pone la ruta del destino como el actual para la funcion de recorrer
//y se busca el menor peso que no este marcado como visitado
//se marca como visitado y se repite la recursion desde ese nodo

void dijkstra(Laberinto G,int nodoInicial){
    int peso[G.cantNodos];
    int ruta[G.cantNodos];
    bool def[G.cantNodos];
    int destino;


    destino=599;
    for (int i=0;i<G.cantNodos;i++){
        peso[i]=10000;
        def[i]=false;
        ruta[i]=0;
    }
    int actual=nodoInicial;
    def[actual]=true;
    peso[actual]=0;
    int menor;
    int contador=0;
    while(def[destino]==false){
            contador+=1;
        AList<int> vecinos=G.getListaVecinos(actual);
        //recorre la lista de vecinos del nodo actual
        for (vecinos.moveToStart();vecinos.currPos()<vecinos.length();vecinos.next()){
            if ((peso[actual]+1<peso[vecinos.getValue()])&&(def[vecinos.getValue()]==false)){
                peso[vecinos.getValue()]=peso[actual]+1;
                ruta[vecinos.getValue()]=actual;
            }
        }
        menor=10000;// para sacar el menor no selecionado
        //y realizar una especie de metodo burbuja
        for (int i=0;i<G.cantNodos;i++){
            if ((peso[i]<menor)&& (def[i]==false)){
                menor=peso[i];
                actual=i;
            }
        }
        def[actual]=true;
    }
    //empieza el recorrido con el arreglo de la ruta mas corta
    recorrido(ruta,599);
}
    // Resetea los atributos del grafo.
    void limpiarGrafo(){
        aristas=0;
        cantNodos=0;
        visitas=1;
        for (int i =0;i<this->cantNodos;i++){
            nodo[i].clear();
            visitado[i]=0;
        }
    }
};




#endif // GRAFO_H_INCLUDED
