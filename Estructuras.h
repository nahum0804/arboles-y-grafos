// estructuras.h
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <list>
#include <string>

using namespace std;

struct Vertice;

struct Arco {
    int distancia;
    Vertice* destino;

    Arco(int dist, Vertice* dest);
};

struct Vertice {
    string nombre;
    list<string> actividades;
    list<Arco> arcos;
    Vertice* siguiente;

    // Constructor
    Vertice(const string& nombre);
    
    // Agregar
    void addActividad(const string& actividad);
    void addArco(int distancia, Vertice* destino);

    // Remover
    void removeActividad(const string& actividad);
    void removeArco(const Arco& arco);
};


#endif