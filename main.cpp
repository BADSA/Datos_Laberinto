#include <iostream>
#include <winbgim.h>
#include "Laberinto.h"
#include "List.h"
#include<stdlib.h>
#include<time.h>
#include <fstream>
#include "guardar.h"

using namespace std;
//Variables para manejar la libreria y dibujar el laberinto en terminos de ejes "X" y "Y"
int xF=25;
int yF=25;
int x,y;
int tamLinea = 30;

//funciones creadas para hacer punteros a funciones
//ya que si una funcion esta por debajo de la otra y se necesitan
//las funciones no se encuantra una o la otra.
void menuPrincipal();
void menuCargar(Laberinto L=NULL);
void menuGenerar(Laberinto L = NULL);

//Funciones para modificar los ejes x y y;
//Funciones trabajan sin parametros
//modifican las cordenadas y trazan una linea del para ordenado que se le pase como parametro
void movDer(){ x+=tamLinea; lineto(x,y);}
void movIzq(){ x-=tamLinea; lineto(x,y);}
void movAba(){ y+=tamLinea; lineto(x,y);}
void movArr(){ y-=tamLinea; lineto(x,y);}

//Funcion para dibujar el grafo;
//Esta funcion solo recibe por parametro un grafo de tipo laberinto, el cual
//con un ciclo se revisa los nodos vecinos, si el numero menos el contador "i"
//que significaria el nodo actual en el ciclo es (30,31,1,-1), se trasan las lineas
//segun este numero.
//despues de dibujar se coloca el "cursor en las cordenadas x,y correspondientes al nodo siguiente para dibujar"
//si el nuero es %30 genera un cambio de linea para continuar dibujando

void dibujaGrafo(Laberinto G){
    int grosorLinea = 13;
    setlinestyle(1,1,grosorLinea);
    xF=25;//se reinician la variables
    yF=25;
    x = xF;
    y = yF;
    bool cambiarFila = false;//cambiar fila si es %30
    moveto(x,y);
    int ciclo = G.getCantidadNodos();//ciclo depende de la cantidad de nodos del Grafo
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
        for (vecinos.moveToStart();vecinos.currPos()<vecinos.length();vecinos.next()){//ciclo verifica los vecinos
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
}

//Menu cargar
//Recibe por parametro un Grafo, recuperado del archivo .dat del laberito
//con este grafo se trabajan diferentes operaciones dentro del menu
//se puede selecionar el laberinto y cuando este cargado entonces solucionarlo
void menuCargar(Laberinto labRecuperado){
    system("cls");//llamada al sistema para limpiar la consola
    void (*mPrim)();//puntero a menuprincipal
    mPrim=menuPrincipal;
    Laberinto solucion(600);
    if (labRecuperado.getCantAristas()!=0){
            solucion.dijkstra(labRecuperado,0);//solucionar laberinto si se recupera del archivo
    }
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
            cin>>num;
            Arreglo a1=leerArchivo(num);
            if (a1.getNumeroArreglo()==num){
                Laberinto resultante = integraArreglo(a1);//integra arreglo convierte un arreglo en un grafo
                initwindow(940,650);//inicializacion de ventana
                outtextxy (15,625,"Por favor regrese a la consola para contunuar con el programa. ");//msj para el usuarioo
                setcolor(15);//color de la linea
                dibujaGrafo(resultante);//dibuja el grafo resultante recuperado del archivo
                menuCargar(resultante);//se devuelve el grafo como parametro para solucionarlo.
            }else{
                cout<<"No se ha encontrado ningun Laberinto con este identificador."<<endl;
                system("pause");
                menuPrincipal();
            }
    }
    if (op=='2'){
            if (solucion.getCantAristas()!=0){
                setcolor(3); //cambiar de color la linea para solucionarlo
                dibujaGrafo(solucion);//dibujar el grafo solucion la solucion
                outtextxy (15,625,"Selecione esta ventatana y presione cualquier tecla para continuar...");//msj para el usuario
                getch();//deja en espera la ventana donde se dibuja
                closegraph();//cierra la ventana donde se dibuja el grafo
                menuPrincipal();//retorna al menu principal
            }else{//msj si no se encuentra ningun laberinto
                cout<<"No se ha cargado ningun laberinto, por favor indique un laberinto a cargar"<<endl;
                system("pause");
                menuCargar(NULL);
            }
    }
    if (op=='3'){
        if (labRecuperado.getCantAristas()!=0){//si la ventana de generar esta abierta dibuja la solucion y cierra la ventana
            setcolor(3);
            dibujaGrafo(solucion);
            closegraph();
        }
        mPrim();//retorna al menu principal
    }
    else{//msj por si lo digitado no es correcto
            cout<<endl;
            cout<<"La opcion digitada es incorrecta"<<endl;
            cout<<endl;
            menuCargar(NULL);
    }
}

//Menu para generar un laberinto X
//Recibe el laberinto generado por el menu para poderlo solucionar, si no existe ninguno la
//funcionn empieza con el laberinto en NULL

void menuGenerar(Laberinto L ){
    srand(time(NULL));
    system("cls");
    //creacion de los grafos necesarios para generar el Laberinto y su solucion.
    Laberinto lleno(600);
    lleno.crearTodasAristas();
    Laberinto resultante(600);
    resultante.profundidad(lleno,0);
    Laberinto solucion(600);
    //si se pasa un grafo resultante entonces se genera la solcion del mismo nada mas para imprimir
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
    cout<<endl;
    cout<<"Digite una opcion: ";
    cin>>op;
    if (op=='1'){
            if (L.getCantAristas()==0){//si no se ha generado ningun laberinto lo crea
                initwindow(940,650);
                outtextxy (15,625,"Por favor regrese a la consola para contunuar con el programa. ");
                setcolor(15);
                dibujaGrafo(resultante);//dibuja el grafo
                menuGenerar(resultante);
            }else{
                cout<<"La opcion generar ya fue selecionada, ahora se cerrara la ventana del Laberinto"<<endl;
                system("pause");
                setcolor(3);//se necesita dibujar la solcion aunque no se pida y no se ve ante el usuario
                //hasta este punto se toma esta decision como medida drastica ante el error que no se
                //podia generar mas de un laberinto, esto dibuja la solucion del laberinto
                //y deja continuar con el programa normalmente
                dibujaGrafo(solucion);
                closegraph();
                menuPrincipal();
            }
    }
    if (op=='2'){//solcion del Laberinto pasado por parametro
            if (L.getCantAristas()!=0){//ver si ya exite alguna solucion
                setcolor(3);
                dibujaGrafo(solucion);
                outtextxy (15,625,"Selecione esta ventatana y presione cualquier tecla para continuar...");
                getch();
                closegraph();
                menuPrincipal();
            }else{//msj para el usuarioo
                cout<<"No se ha generado ningun Laberinto para solucionar."<<endl;
                system("pause");
                menuGenerar(NULL);
            }
    }
    if (op=='3'){
            if (L.getCantAristas()!=0){
                //se necesita dibujar la solcion aunque no se pida y no se ve ante el usuario
                //hasta este punto se toma esta decision como medida drastica ante el error que no se
                //podia generar mas de un laberinto, esto dibuja la solucion del laberinto
                //y deja continuar con el programa normalmente
                setcolor(3);
                dibujaGrafo(solucion);
                closegraph();
                solucion.dijkstra(L,0);//probablemente inecesario
                listaArchivo();//se muestra la lista de grafos guardados en el documento
                escribirArchivo(L);//se pasa por parametro el grafo que es modificado en la funcion de escribir el
                //archivo para volverlo un objeto de clase arreglo y poderlo guardar
            }else{//msj para el usuario
                cout<<"No se ha generado ningun laberinto, por favor elija la opcion generar para guardar laberinto"<<endl;
                system("pause");
                menuGenerar(NULL);
            }
            menuPrincipal();
    }
    if (op=='4'){
        if (L.getCantAristas()!=0){
                //se necesita dibujar la solcion aunque no se pida y no se ve ante el usuario
                //hasta este punto se toma esta decision como medida drastica ante el error que no se
                //podia generar mas de un laberinto, esto dibuja la solucion del laberinto
                //y deja continuar con el programa normalmente
            setcolor(3);
            dibujaGrafo(solucion);
            closegraph();
        }
        mPrim();
    }
    else{//msj para el ususario si lo que se digita es invalido
        cout<<endl;
        cout<<"La opcion digitada es incorrecta"<<endl;
        cout<<endl;
        menuCargar(NULL);
    }
}
//Menu principal del programa
//este seleciona que parte del programa se debe ejecutar segun la decision del ususario
//se mueve entre las funciones de los otros menu

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
    switch (op){//decisiones segun el usuario
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
    menuPrincipal();
    return 0;
}

//Desarrolladores BADSA.Corp
//Melvin Elizondo
//Daniel Solis Mendez
//en colaboracion con Jose Roberto Arguedas
