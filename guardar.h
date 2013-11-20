#ifndef GUARDAR_H_INCLUDED
#define GUARDAR_H_INCLUDED
//librerias necesarias para las funciones creadas
#include <iostream>
#include<stdlib.h>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Laberinto.h"

using namespace std;
//clase creada para el manejo de los archivos

class Arreglo{
public:
    int vertices[2400];
    int numeroArreglo=0;
    char nombreArreglo[10];
    void setNumeroArreglo(int num){
        numeroArreglo=num;
    }
    int getNumeroArreglo()const {
        return numeroArreglo;
    }
    void setNombreLab(string nombre){
        nombre.resize(9);
        strcpy(nombreArreglo, nombre.c_str());
    }
    string getNombreLab() const {
        return nombreArreglo;
    }
    void imprimeArreglo(){
        for (int i=0;i<2400;i++){
            cout<<vertices[i]<<" ";
        }
    }
    Arreglo(int num=0){
        numeroArreglo=num;
    }
};
//Funcion que recive un objeto tipo arreglo.
//Utiliza dentro de esta un objeto tipo Laberinto para integrar el
//arreglo traducido en un grafo resultante para generar el laberinto
//retorna un objero tipo Laberito que es el grafo.

Laberinto integraArreglo(Arreglo a1){
    Laberinto resultante(600);
    int contador=0;
    for(int i=0;i<2400;i++){
        int num=a1.vertices[i];
        if ((i%4==0)&&(i!=0)){
            contador+=1;
        }
        if (num!=-1){
            resultante.setAristaIndividual(contador,num);
        }
    }
    return resultante;
}
//funcion inversa para integrar arreglo
//este recibe un grafo y lo convierte en un objero tipo arreglo
//para poderlo devolver
Arreglo llenarArregloVecinos(Laberinto G){
    Arreglo a1;
    int vertices[G.cantNodos*4];
    //cout<<G.cantNodos*4<<endl;
    int i=0;
    //se hace un ciclo con la lista de los nodos vecinos
    //se pide la cantidad de vecinos
    //con esto se llena el arreglo con -1 los vecinos que no existan
    //en orden de 4 espacios por nodo
    for (int j=0;j<G.cantNodos;j++){
            AList<int> vecinos=G.getListaVecinos(j);
            vecinos.moveToStart();
            if (vecinos.length()==0){
                vertices[i]=vertices[i+1]=vertices[i+2]=vertices[i+3]=-1;
            }
            if (vecinos.length()==1){
                vertices[i]=vecinos.getValue();
                vertices[i+1]=vertices[i+2]=vertices[i+3]=-1;
            }
            if (vecinos.length()==2){
                vertices[i]=vecinos.getValue();vecinos.next();
                vertices[i+1]=vecinos.getValue();
                vertices[i+2]=vertices[i+3]=-1;
            }
            if (vecinos.length()==3){
                vertices[i]=vecinos.getValue();vecinos.next();
                vertices[i+1]=vecinos.getValue();vecinos.next();
                vertices[i+2]=vecinos.getValue();
                vertices[i+3]=-1;
            }
            if (vecinos.length()==4){
                vertices[i]=vecinos.getValue();vecinos.next();
                vertices[i+1]=vecinos.getValue();vecinos.next();
                vertices[i+2]=vecinos.getValue();vecinos.next();
                vertices[i+3]=vecinos.getValue();
            }
            i+=4;
    }
    //se pasa el arreglo local al arreglo que esta en el atributo de la clase para retornarlo
    for (int i=0;i<2400;i++){
        a1.vertices[i]=vertices[i];
    }
    return a1;
}

//funcion sin parametros para inicializar el archivo
//se crean en el archivo 100 espacios del tamano de la clase listos para utilizar

void inicializarArchivo() {
    ofstream LabData;
    LabData.open("saved.dat", ios::out | ios::binary);//se abre el archivo
    if (!LabData.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit( 1 );
    }
    Arreglo a1;
    for (int i = 0; i < 100; i++) {
       LabData.write(reinterpret_cast<const char *>( &a1 ), sizeof( Arreglo ) );
    }
}
//Fucion recibe como parametro un Grafo
//este se convierte en un arreglo para poderlo almacenar consistentemente
//luego se pide un identificador para el arreglo para poderlo utilizar y convertir en grafo cuando se desee.
//la funcion tiene como salida en el documento .dat

void escribirArchivo(Laberinto g1){
    Arreglo arreglo;
    arreglo=llenarArregloVecinos(g1);//conversion del grafo a arreglo
    char nombreLab[10];//arreglo de char para hacer un string para el nombre del laberinto

    fstream LabData("saved.dat",ios::in | ios::out | ios::binary);//modo para abrir el archivo
    if (!LabData.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit( 1 );
    }
    cout<<"Digite un numero para guardar el Laberinto: ";
    int numArreglo;
    cin >> numArreglo;
    cout<<endl;
    while ( numArreglo > 0 && numArreglo <= 100 ) {//ciclo para moverse por los sectores del archivo, los identificadores del
            //arreglo estan en cero, por eso se pone q sea menor a 0 y mayor a 100 para buscarlos despues en otra funcion
            arreglo.setNumeroArreglo(numArreglo);
            cout<<"Digite un nombre asociado a su laberinto: ";
            cin>>setw(9)>>nombreLab;
            arreglo.setNombreLab(nombreLab);
            LabData.seekp((arreglo.getNumeroArreglo() - 1) * sizeof(Arreglo));
            LabData.write(reinterpret_cast<const char *>(&arreglo), sizeof(Arreglo));//metodo para moverse por el archivo
            numArreglo=0;//necesario para terminar el ciclo
    }
}
//Funcion para recuperar un n arrglo del archivo
//recibe por parametro un numero correspondiente al identificador del arreglo;
//retorna un objeto tipo arreglo el cuan contiene el arreglo correspondiente al Grafo
Arreglo leerArchivo(int num){
    Arreglo arreglo2;
    ifstream test2("saved.dat", ios::in | ios::binary);
    cout<<"Digite el numero de Laberinto\n->";
    test2.read(reinterpret_cast<char *>(&arreglo2), sizeof(Arreglo));
    while ( test2.good() ) {
        if ( arreglo2.getNumeroArreglo() == num ) {
            break;
        }
        test2.read(reinterpret_cast<char *>(&arreglo2), sizeof(Arreglo));
    }
    test2.close();
    return arreglo2;
}
//funcion creada para ver los grafos almacenados
//como informacion para guiar al ususario;
//desplega todos los grafos alamacenados en el documento.
void listaArchivo(){
    cout<<"             Lista de laberintos almacenados"<<endl;
    cout<<"Utilice el numero asociado al nombre del laberinto para cargarlo cuando desee.\n"<<endl;
    Arreglo arreglo2;
    ifstream test2("saved.dat", ios::in | ios::binary);
    test2.read(reinterpret_cast<char *>(&arreglo2), sizeof(Arreglo));
    while ( test2.good() ) {
        if ( arreglo2.getNumeroArreglo() != 0 ) {
            cout<<"Numero de Laberinto: "<<arreglo2.getNumeroArreglo()<<". ";
            cout<<"Nombre asociado al laberinto: "<<arreglo2.getNombreLab()<<endl;
        }
        test2.read(reinterpret_cast<char *>(&arreglo2), sizeof(Arreglo));
    }
    test2.close();
}

#endif // GUARDAR_H_INCLUDED
