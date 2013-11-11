#include <iostream>
#include <winbgim.h>
//#include "Grafo.h"
#include "List.h"

int x=10;
int y=10;
void menuPrincipal();
void menuCargar();

using namespace std;
void movDer(){x+=100; lineto(x,y);}
void movIxz(){x-=100; lineto(x,y);}
void movAba(){y+=100; lineto(x,y);}
void movArr(){y-=100; lineto(x,y);}
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

int main()
{
    return 0;
}
