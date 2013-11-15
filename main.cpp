#include <iostream>
#include <winbgim.h>
#include "Laberinto.h"
#include "List.h"
#include<stdlib.h>
#include<time.h>

int xF=25;
int yF=25;
int x,y;

bool arriba=false;
bool abajo=false;
bool derecha=false;
bool izquierda=false;

void menuPrincipal();
void menuCargar();


void movDer(){ x+=25; lineto(x,y); derecha=true;  izquierda=arriba=abajo=false;}
void movIzq(){ x-=25; lineto(x,y); izquierda=true; derecha=arriba=abajo=false;}
void movAba(){ y+=25; lineto(x,y); abajo=true;  izquierda=arriba=derecha=false;}
void movArr(){ y-=25; lineto(x,y); arriba=true;  izquierda=derecha=abajo=false;}



using namespace std;

void menuGenerar(){
    system("cls");
    char op;
    void (*mPrim)();
    mPrim=menuPrincipal;
    cout<<"Generador de Laberintos BADSA.Corp"<<endl;
    cout<<"    Menu Generar"<<endl;
    cout<<"1-Inidicar tamano del laberinto"<<endl;
    cout<<"2-Indicar algoritmo de generacion"<<endl;
    cout<<"3-Solucionar el laberinto"<<endl;
    cout<<"4-Guardar el laberinto"<<endl;
    cout<<"5-Regresar"<<endl;
    cin>>op;
    switch (op){
        case '1':
           // menuGenerar();
            break;
        case '2':
           // menuCargar();
            break;
        case '3':
            mPrim();
            break;
        case '4':
            //mPrim();
            break;
        case '5':
            mPrim();
            break;
        default:
            cout<<endl;
            cout<<"La opcion digitada es incorrecta"<<endl;
            cout<<endl;
            menuCargar();
            break;
    }
}

void menuCargar(){
    system("cls");
   // cout<<"\x1B[2J\x1B[H";
    void (*mPrim)();
    mPrim=menuPrincipal;
    char op;
    cout<<"Generador de Laberintos BADSA.Corp"<<endl;
    cout<<"    Menu Cargar"<<endl;
    cout<<"1-Indicar laberinto a carga"<<endl;
    cout<<"2-Solucionar laberinto"<<endl;
    cout<<"3-Regresar"<<endl;
    cout<<"Digite la opcion deseada"<<endl;
    cin>>op;
    switch (op){
        case '1':
            break;
        case '2':
            break;
        case '3':
            mPrim();
            break;
        default:
            cout<<endl;
            cout<<"La opcion digitada es incorrecta"<<endl;
            cout<<endl;
            menuCargar();
            break;
    }
}

void menuPrincipal(){
    system("cls");
    char op;

    cout<<"Generador de Laberintos BADSA.Corp"<<endl;
    cout<<"    Menu Principal"<<endl;
    cout<<"1-Generar laberinto"<<endl;
    cout<<"2-Cargar laberinto"<<endl;
    cout<<"3-Salir"<<endl;
    cout<<"Digite la opcion deseada"<<endl;
    cin>>op;
    switch (op){
        case '1':
            menuGenerar();
            break;
        case '2':
            menuCargar();
            break;
        case '3':
            exit(0);
            break;
        default:
            cout<<endl;
            cout<<"La opcion digitada es incorrecta"<<endl;
            cout<<endl;
            menuPrincipal();
            break;
    }
}



int dibujaGrafo(Laberinto G){
    initwindow(800,700);
    int grosorLinea = 2;
    setlinestyle(1,1,grosorLinea);
    x = xF;
    y = yF;
    bool cambiarFila = false;
    moveto(x,y);
    setcolor(15);

    int ciclo = G.getCantidadNodos();
    //cout<<ciclo<<endl;
    for (int i=0;i<ciclo;i++){
        AList<int> vecinos= G.getListaVecinos(i);
        if (cambiarFila){
            x=xF;
            yF+=25;
            y=yF;
            moveto(x,y);
            cambiarFila = false;
        }
        setcolor(3);
        circle(x,y,5);
        setcolor(15);

        if ( ((i + 1) % 30) == 0 ){
            if (vecinos.length()==0){
                cambiarFila = true;
            }
        }

        for (vecinos.moveToStart();vecinos.currPos()<vecinos.length();vecinos.next()){
            int decision = vecinos.getValue() - i;
            //cout<<i<<" vecino "<<vecinos.getValue()<<endl;
            if (decision==-1){
                    movIzq();
                    movDer();
            }
            if (decision==1){
                movDer();
                movIzq();
            }

            if (decision==30){
                movAba();
                movArr();
            }
            if (decision==-30){
                    movArr();
                    movAba();
            }

            if (vecinos.currPos() + 1 == vecinos.length() ){
                if ( ((i + 1) % 30) == 0 ){
                    cambiarFila = true;
                }else{
                    x+=25;
                    moveto(x,y);
                }
            }

        }
    }
    getch();
    return 0;
}
int main()
{
    //initwindow (600,400); //Tamaño de nuestra ventana
    srand(time(NULL));
    Laberinto lleno(600);
    lleno.crearTodasAristas();
    return 0;
}
