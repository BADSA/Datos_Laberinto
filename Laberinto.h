#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "List.h"
#include "AList.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

class Laberinto{
public:
    AList<int> * nodo;
    int *visitado;
    int aristas=0;
    int cantNodos=0;
    int visitas = 1;


    void init(int cant){
        this->nodo = new AList<int> [cant];
        this->visitado = new int[cant];
        this->cantNodos = cant;
        for(int i=0;i<cant;i++){
            visitado[i]=0;
        }
    }

public:
    Laberinto(int cant){
        init(cant);
    }

    int getCantidadNodos(){
        return cantNodos;
    }

    int isVisitado(int numNodo){
        return this->visitado[numNodo];
    }

    void setVisitado(int numNodo){
        this->visitado[numNodo] = 1;
    }

    int getCantVecinos(int numNodo){
        return this->nodo[numNodo].length();
    }

    void setArista(int a, int b){
        this->nodo[a].append(b);
        this->nodo[b].append(a);
        this->aristas += 1;
    }

    void setAristaIndividual(int a, int b){
        this->nodo[a].append(b);
        this->aristas += 1;
    }

    int getCantAristas(){
        return this->aristas;
    }

    int getVecinoAleatorio(int numNodo){
        int cant = this->getCantVecinos(numNodo);
        int aleatorio = rand() % cant;
        this->nodo[numNodo].moveToPos(aleatorio);
        return this->nodo[numNodo].getValue();
    }

    AList<int> getListaVecinos(int numNodo){
        AList<int> temporal(4);
        for (nodo[numNodo].moveToStart();nodo[numNodo].currPos()<nodo[numNodo].length();nodo[numNodo].next()){
            temporal.append(nodo[numNodo].getValue());
        }
        return temporal;
    }

    void crearTodasAristas(){
        for (int i=0; i <20;i++){
            for (int j=0; j<29; j++){
                this->setArista( j+(i*30), j+(i*30)+1 );
            }
        }
        for (int i=0; i < 30;i++){
            for (int j=i; j<570; j+=30){
                this->setArista( j, j+30 );
            }
        }
    }

    void profundidad(Laberinto G,int numNodo){
        this->setVisitado(numNodo);
        AList<int> vecinos = G.getListaVecinos(numNodo);
        vecinos.shuffle();

        for (vecinos.moveToStart(); vecinos.currPos()<vecinos.length() ; vecinos.next()){
            if ( (this->isVisitado(vecinos.getValue()))== 0 ) {
                this->setAristaIndividual(numNodo,vecinos.getValue());
                visitas ++;
                profundidad(G,vecinos.getValue());
            }
        }
    }

void recorrido(int *ruta,int nodo){
    if (ruta[nodo]==0){
            cout<<ruta[nodo]<<" ";
            this->setArista(nodo,ruta[nodo]);
            //dibujaGrafo(gSolucion);
            return;
    }
    this->setArista(nodo,ruta[nodo]);
    cout<<ruta[nodo]<<" ";
    recorrido(ruta,ruta[nodo]);
}
    void dijkstra(Laberinto G,int nodoInicial){
    int peso[G.cantNodos];
    int ruta[G.cantNodos];
    bool def[G.cantNodos];
    int destino;

    //peso=new int[G.cantNodos];
   // def=new bool[G.cantNodos];
    //ruta=new int[G.cantNodos];
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
        //cout<<actual<<" ";//<<endl;
        AList<int> vecinos=G.getListaVecinos(actual);
        //recorre la lista de vecinos del nodo actual
        for (vecinos.moveToStart();vecinos.currPos()<vecinos.length();vecinos.next()){
                cout<<vecinos.getValue()<<" ";
            if ((peso[actual]+1<peso[vecinos.getValue()])&&(def[vecinos.getValue()]==false)){
                //cout<<vecinos.getValue()<<" ";
                peso[vecinos.getValue()]=peso[actual]+1;
                ruta[vecinos.getValue()]=actual;
            }
        }
        menor=10000;
        for (int i=0;i<G.cantNodos;i++){
            if ((peso[i]<menor)&& (def[i]==false)){
                menor=peso[i];
                actual=i;
            }
        }
        def[actual]=true;
        //cout<<actual<<endl;
    }
    recorrido(ruta,599);
}

};




#endif // GRAFO_H_INCLUDED
