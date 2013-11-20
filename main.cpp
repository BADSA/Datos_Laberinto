#include <iostream>
#include <winbgim.h>
#include "Laberinto.h"
#include "List.h"
#include<stdlib.h>
#include<time.h>
#include <fstream>
#include "guardar.h"

using namespace std;

int xF=25;
int yF=25;
int x,y;
int tamLinea = 30;

bool arriba=false;
bool abajo=false;
bool derecha=false;
bool izquierda=false;

void menuPrincipal();
void menuCargar(Laberinto L=NULL);
void menuGenerar(Laberinto L = NULL);

void movDer(){ x+=tamLinea; lineto(x,y); derecha=true;  izquierda=arriba=abajo=false;}
void movIzq(){ x-=tamLinea; lineto(x,y); izquierda=true; derecha=arriba=abajo=false;}
void movAba(){ y+=tamLinea; lineto(x,y); abajo=true;  izquierda=arriba=derecha=false;}
void movArr(){ y-=tamLinea; lineto(x,y); arriba=true;  izquierda=derecha=abajo=false;}


void dibujaGrafo(Laberinto G){
    //initwindow(1000,700);
    int grosorLinea = 13;
    setlinestyle(1,1,grosorLinea);
    xF=25;
    yF=25;
    x = xF;
    y = yF;
    bool cambiarFila = false;
    moveto(x,y);
    int ciclo = G.getCantidadNodos();
    for (int i=0;i<ciclo;i++){
        Sleep(1);
        AList<int> vecinos= G.getListaVecinos(i);
        if (cambiarFila){
            x=xF;
            yF+=tamLinea;
            y=yF;
            moveto(x,y);
            cambiarFila = false;
        }
        for (vecinos.moveToStart();vecinos.currPos()<vecinos.length();vecinos.next()){
            int decision = vecinos.getValue() - i;
            if (decision==-1){
                movIzq(); movDer();
            }
            if (decision==1){
                movDer(); movIzq();
            }
            if (decision==30){
                movAba(); movArr();
            }
            if (decision==-30){
                movArr(); movAba();
            }
        }
        if ( ((i + 1) % 30) == 0 ){
            cambiarFila = true;
        }else{
            x+=tamLinea;
            moveto(x,y);
        }
    }
    //getch();
    //closegraph( );
}


void solucionarLab(string clave,Laberinto G1=NULL){
    Laberinto lleno(600);
    lleno.crearTodasAristas();
    Laberinto resultante(600);
    Laberinto solucion(600);
    solucion.dijkstra(resultante,0);
    setcolor(3);
    dibujaGrafo(solucion);
    solucion.limpiarGrafo();
    resultante.limpiarGrafo();
    void (*funct)(Laberinto) = menuGenerar;
    funct(resultante);
}
Laberinto generarLab(){
    Laberinto lleno(600);
    lleno.crearTodasAristas();
    Laberinto resultante(600);
    resultante.profundidad(lleno,0);
    initwindow(940,650);
    setcolor(15);
    outtextxy (15,625,"Por favor regrese a la consola para contunuar con el programa. ");
    dibujaGrafo(resultante);
    setcolor(3);
    void (*funct)(Laberinto) = menuGenerar;
    funct(resultante);
}
void menuCargar(Laberinto labRecuperado){
    system("cls");
    void (*mPrim)();
    Laberinto solucion(600);
    if (labRecuperado.getCantAristas()!=0){
            solucion.dijkstra(labRecuperado,0);
    }
    mPrim=menuPrincipal;
    char op;
    cout<<"Generador de Laberintos BADSA.Corp"<<endl;
    cout<<"    Menu Cargar"<<endl;
    cout<<"1-Indicar laberinto a cargar"<<endl;
    cout<<"2-Solucionar laberinto"<<endl;
    cout<<"3-Regresar"<<endl;
    cout<<"Digite la opcion deseada"<<endl;
    cin>>setw(1)>>op;
    if (op=='1'){
            system("cls");
            listaArchivo();
            cout<<"Digite el numero de laberinto a cargar: ";
            int num;
            cin>>setw(2)>>num;
            Arreglo a1=leerArchivo(num);
            if (a1.getNumeroArreglo()==num){
                Laberinto labRecuperado = integraArreglo(a1);
                initwindow(1000,700);
                setcolor(15);
                dibujaGrafo(labRecuperado);
                menuCargar(labRecuperado);
            }else{
                cout<<"No se ha encontrado ningun Laberinto con este identificador."<<endl;
                system("pause");
                menuPrincipal();
            }
    }
    if (op=='2'){
            if (solucion.getCantAristas()!=0){
                setcolor(3);
                dibujaGrafo(solucion);
                outtextxy (15,625,"Selecione esta ventatana y presione cualquier tecla para continuar...");
                getch();
                closegraph();
                menuPrincipal();
            }else{
                cout<<"No se ha cargado ningun laberinto, por favor indique un laberinto a cargar"<<endl;
                system("pause");
                menuGenerar(NULL);
            }
    }
    if (op=='3'){
            mPrim();
    }

    else{
            cout<<endl;
            cout<<"La opcion digitada es incorrecta"<<endl;
            cout<<endl;
            menuCargar(NULL);
    }
}

void menuGenerar(Laberinto L ){
    system("cls");
    Laberinto solucion(600);
    if (L.getCantAristas()!=0){
            solucion.dijkstra(L,0);
    }
    char op;
    void (*mPrim)();
    mPrim=menuPrincipal;
    cout<<"Generador de Laberintos BADSA.Corp"<<endl;
    cout<<"    Menu Generar"<<endl;
    cout<<"1-Generar laberinto"<<endl;
    cout<<"2-Solucionar el laberinto"<<endl;
    cout<<"3-Guardar el laberinto"<<endl;
    cout<<"4-Regresar"<<endl;
    cin>>op;
    switch (op){
        case '1':
            generarLab();
            break;
        case '2':
            if (L.getCantAristas()!=0){
                setcolor(3);
                dibujaGrafo(solucion);
                outtextxy (15,625,"Selecione esta ventatana y presione cualquier tecla para continuar...");
                getch();
                closegraph();
                menuPrincipal();
            }else{
                cout<<"No se ha generado ningun Laberinto para solucionar."<<endl;
                system("pause");
                menuGenerar(NULL);
            }
            break;
        case '3':
            if (L.getCantAristas()!=0){
                closegraph();
                solucion.dijkstra(L,0);
                escribirArchivo(L);
            }else{
                cout<<"No se ha generado ningun laberinto, por favor elija la opcion generar para guardar laberinto"<<endl;
                system("pause");
                menuGenerar(NULL);
            }
            menuPrincipal();
            break;
        case '4':
            closegraph();
            mPrim();
            break;
        default:
            cout<<endl;
            cout<<"La opcion digitada es incorrecta"<<endl;
            cout<<endl;
            menuCargar(NULL);
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
            menuCargar(NULL);
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
    srand(time(NULL));
    //inicializarArchivo();
    menuPrincipal();




    return 0;
}
