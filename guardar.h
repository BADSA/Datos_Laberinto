#ifndef GUARDAR_H_INCLUDED
#define GUARDAR_H_INCLUDED

#include <iostream>
#include<stdlib.h>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Laberinto.h"

using namespace std;

class Arreglo{
public:
    int vertices[2400];
    int numeroArreglo;
    char nombreArreglo[10];
    Arreglo(){}
    void setNumeroArreglo(int num){
        numeroArreglo=num;
    }
    int getNumeroArreglo(){
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
    //arreglo2 = new int[2400];
};
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

Arreglo llenarArregloVecinos(Laberinto G){
    Arreglo a1;
    int vertices[G.cantNodos*4];
    //cout<<G.cantNodos*4<<endl;
    int i=0;
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
    for (int i=0;i<2400;i++){
        a1.vertices[i]=vertices[i];
    }
    return a1;
}


void inicializarArchivo() {
    ofstream LabData;
    LabData.open("saved.dat", ios::out | ios::binary);
    if (!LabData.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit( 1 );
    }
    Arreglo a1;
    for (int i = 0; i < 100; i++) {
       LabData.write(reinterpret_cast<const char *>( &a1 ), sizeof( Arreglo ) );
    }
}
void escribirArchivo(Laberinto g1){
    Arreglo arreglo=llenarArregloVecinos(g1);
    int *arreglo2;
    arreglo2=new int[2400];
    char nombreLab[10];
    fstream test("saved.dat", ios::out | ios::binary);
    if (!test.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit( 1 );
    }
    cout<<"Digite un numero para guardar el arreglo: ";
    int numArreglo;
    cin >> numArreglo;
    cout<<endl;
    while ( numArreglo > 0 && numArreglo <= 100 ) {
            arreglo.setNumeroArreglo(numArreglo);
            cout<<"Digite un nombre asociado a su laberinto: ";
            cin>>setw(9)>>nombreLab;
            arreglo.setNombreLab(nombreLab);
            test.seekp((arreglo.getNumeroArreglo() - 1) * sizeof(Arreglo));
            test.write(reinterpret_cast<const char *>(&arreglo), sizeof(Arreglo));
            cout<<"Digite un numero para guardar el arreglo: ";
            cin >> numArreglo;
    }
    test.close();
}
Arreglo leerArchivo(int num){
    Arreglo arreglo2;
    ifstream test2("saved.dat",ios::in | ios::binary);

    cout<<"Digite el numero de Laberinto\n->";
    //cin>>setw(2)>>num;
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

void listaArchivo(){
    cout<<"             Lista de laberintos almacenados"<<endl;
    cout<<"Utilice el numero asociado al nombre del laberinto para cargarlo cuando desee.\n"<<endl;
    Arreglo arreglo2;
    ifstream test2("saved.dat",ios::in | ios::binary);
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
