// estructuras.h
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <list>
#include <string>

using namespace std;

struct Arco;

struct Vertice
{
    string nombre;
    std::list<std::string *> actividades;
    list<Arco> arcos;
    // Vertice *siguiente;
    bool visitado = false;

    // Constructor
    Vertice(const string nombre);

    // Agregar
    void addActividad(const std::string &actividad);
    void addArco(int distancia, string inicio, string destino);
    // void (int distancia, Vertice *destino);

    // Remover
    void removeActividad(const string actividad);
    void removeArco(const Arco arco);

    // Operador de igualdad
    bool operator==(const Vertice &other) const
    {
        return nombre == other.nombre && actividades == other.actividades;
    }
};

struct Arco
{
    int distancia;
    Vertice *destino;

    Arco(int dist, Vertice *dest);
};

#endif