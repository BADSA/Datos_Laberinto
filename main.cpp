#include <iostream>
#include <winbgim.h>
#include "Laberinto.h"
#include "List.h"
#include<stdlib.h>
#include<time.h>
#include <fstream>

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
void menuCargar();
void menuGenerar(Laberinto L = NULL);

void movDer(){ x+=tamLinea; lineto(x,y); derecha=true;  izquierda=arriba=abajo=false;}
void movIzq(){ x-=tamLinea; lineto(x,y); izquierda=true; derecha=arriba=abajo=false;}
void movAba(){ y+=tamLinea; lineto(x,y); abajo=true;  izquierda=arriba=derecha=false;}
void movArr(){ y-=tamLinea; lineto(x,y); arriba=true;  izquierda=derecha=abajo=false;}

void dibujaGrafo(Laberinto G){
    initwindow(1000,700);
    int grosorLinea = 13;
    setlinestyle(1,1,grosorLinea);
    x = xF;
    y = yF;
    bool cambiarFila = false;
    moveto(x,y);
    setcolor(15);
    int ciclo = G.getCantidadNodos();
    for (int i=0;i<ciclo;i++){
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
    getch();
    closegraph( );
}

Laberinto leerLaberinto() {
    fstream labEntrada( "labSaved.dat", ios::in | ios::binary );
    if ( !labEntrada.is_open() ) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit( 1 );
    }
    int numLab;
    cout<< "Digite el numero de laberinto que desea cargar -> ";
    cin >> numLab;
    labEntrada.seekp(0); //(numLab)* sizeof(Laberinto)
    Laberinto lab(600);
    labEntrada.read( reinterpret_cast< char * >( &lab ), sizeof( Laberinto ) );
    return lab;
}




void escribirLaberinto(Laberinto L) {
    fstream labSalida( "labSaved.dat", ios::in | ios::out | ios::binary );
    if ( !labSalida.is_open() ) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit(1);
    }
    cout << "Guardando laberinto..."<<endl;



    /*
    Laberinto lab(600);
    int cantLabGuardados = 0;
    labSalida.seekp(0);
    labSalida.read( reinterpret_cast< char * >( &lab ), sizeof( Laberinto ) );
    cout << lab.getCantAristas()<<endl;
    while ( labSalida.good() ) {
        if ( lab.getCantAristas() > 0 ) {
            cout << "laberinto en pos "<<cantLabGuardados<<endl;
            cantLabGuardados+=1;
        }
        labSalida.read( reinterpret_cast< char * >( &lab ), sizeof( Laberinto ) );
    }
    labSalida.seekp(cantLabGuardados);
    */
    labSalida.write(reinterpret_cast<const char *>(&L), sizeof(Laberinto));
//    cout << "Laberinto guardado correctamente en pos "<<cantLabGuardados<<endl;

    /*
    //cout << "Hay guardados "<<cantLabGuardados << " laberintos."<< endl;
    //labSalida.seekp((cantLabGuardados)* sizeof(Laberinto));
    */
}


void inicializarArchivo() {
    ofstream labSalida;
    labSalida.open("labSaved.dat", ios::out | ios::binary);
    if (!labSalida.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit( 1 );
    }
    Laberinto laberintoEnBlanco(600);
    for (int i = 0; i < 100; i++) {
       labSalida.write( reinterpret_cast<const char *>( &laberintoEnBlanco ), sizeof( Laberinto ) );
    }
}

void genera(string algoritmo){
    Laberinto lleno(600);
    lleno.crearTodasAristas();
    Laberinto resultante(600);
    if (algoritmo == "profundidad") {
            resultante.profundidad(lleno , 255);
    }else if (algoritmo == "prim"){
        cout << "No implementado aun..."<<endl;
        // resultante.prim(lleno , 255);
    }else{
        cout << "No implementado aun..."<<endl;
        // resultante.kruskal(lleno , 255);
    }
    dibujaGrafo(resultante);
    void (*funct)(Laberinto) = menuGenerar;
    funct(resultante);
}


void menuTipoAlgoritmo(){
    system("cls");
    void (*funct)(Laberinto);
    funct = menuGenerar;
    cout<<"    Menu Algoritmo de generacion"<<endl;
    cout<<"1- Profundidad"<<endl;
    cout<<"2- Prim"<<endl;
    cout<<"3- Kruskal"<<endl;
    cout<<"4- Regresar"<<endl;
    char op;
    cin>>op;
    switch (op){
        case '1':
           genera("profundidad");
            break;
        case '2':
            genera("prim");
            break;
        case '3':
            genera("kruskal");
            break;
        case '4':
            funct(NULL);
            break;
        default:
            cout<<endl;
            cout<<"La opcion digitada es incorrecta"<<endl;
            cout<<endl;
            menuTipoAlgoritmo();
    }
}


void menuGenerar(Laberinto L ){
    system("cls");
    char op;
    void (*mPrim)();
    mPrim=menuPrincipal;
    cout<<"Generador de Laberintos BADSA.Corp"<<endl;
    cout<<"    Menu Generar"<<endl;
    cout<<"1-Indicar algoritmo de generacion"<<endl;
    cout<<"2-Solucionar el laberinto"<<endl;
    cout<<"3-Guardar el laberinto"<<endl;
    cout<<"4-Regresar"<<endl;
    cin>>op;
    switch (op){
        case '1':
            menuTipoAlgoritmo();
            break;
        case '2':
            mPrim();
            break;
        case '3':
            escribirLaberinto(L);
            break;
        case '4':
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
    void (*mPrim)();
    mPrim=menuPrincipal;
    char op;
    Laberinto labRecuperado(600);
    cout<<"Generador de Laberintos BADSA.Corp"<<endl;
    cout<<"    Menu Cargar"<<endl;
    cout<<"1-Indicar laberinto a cargar"<<endl;
    cout<<"2-Solucionar laberinto"<<endl;
    cout<<"3-Regresar"<<endl;
    cout<<"Digite la opcion deseada"<<endl;
    cin>>op;
    switch (op){
        case '1':
            system("cls");
            labRecuperado = leerLaberinto();
            dibujaGrafo(labRecuperado);
            menuCargar();
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
    srand(time(NULL));
    //inicializarArchivo();
    menuPrincipal();
    return 0;
}
