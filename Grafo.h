#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "List.h"

using namespace std;
class Grafo{
private:
    LList<int> nodo[600];
    int marca[600];


    void init(int cant){
    }

public:

    Grafo(int cant){
        init(cant);
    }
    int getAristasNodo(int numNodo){
        return nodo[numNodo].length();
    }

    void crearAristas(){
        int cont = 0;
        for (int i=0; i <20;i++){
            for (int j=0; j<29; j++){
                nodo[j+(i*30)].append(j+(i*30)+1);
                nodo[j+(i*30)+1].append(j+(i*30));
                //if ( (j+(i*30) == 50) or (j+(i*30)+1 == 50)){
                //    cout << j+(i*30)<<" arista con "<<j+(i*30)+1<<endl;
                //}

            }

        }


        for (int i=0; i < 30;i++){
            for (int j=i; j<570; j+=30){
                nodo[j].append(j+30);
                nodo[j+30].append(j);
            }
        }
    }

};


#endif // GRAFO_H_INCLUDED
