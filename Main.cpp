#include <iostream>
#include "Estructuras.h"

using namespace std;

Arco::Arco(int dist, Vertice* dest) : distancia(dist), destino(dest) {}

// Implementación del constructor de Vertice
Vertice::Vertice(const string& nombre) : nombre(nombre) {}

// Implementación de la función para agregar actividades
void Vertice::addActividad(const string& actividad) {
    actividades.push_back(actividad);
}

// Implementación de la función para agregar arcos
void Vertice::addArco(int distancia, Vertice* destino) {
    arcos.push_back(Arco(distancia, destino));
}


//Prototypes 
void showVerticeData(Vertice* vertice);


int main() {

    //-------- Carga de Datos ---------

    // Creación de vértices
    Vertice v1("Ciudad Quesada");
    Vertice v2("La Fortuna");
    Vertice v3("Rio Celeste");
    Vertice v4("Poas");
    Vertice v5("San Jose");
    Vertice v6("Liberia");
    Vertice v7("Pital");

    // Conexiones entre vértices (arcos)
    v1.addArco(30, &v2);
    v1.addArco(50, &v3);
    v1.addArco(40, &v4);
    v1.addArco(80, &v5);
    v1.addArco(110, &v6);
    v1.addArco(20, &v7);

    v2.addArco(30, &v1);
    v2.addArco(20, &v3);
    v2.addArco(40, &v4);
    v2.addArco(70, &v5);
    v2.addArco(100, &v6);
    v2.addArco(50, &v7);

    v3.addArco(50, &v1);
    v3.addArco(20, &v2);
    v3.addArco(30, &v4);
    v3.addArco(60, &v5);
    v3.addArco(90, &v6);
    v3.addArco(70, &v7);

    v4.addArco(40, &v1);
    v4.addArco(30, &v2);
    v4.addArco(30, &v3);
    v4.addArco(50, &v5);
    v4.addArco(80, &v6);
    v4.addArco(60, &v7);

    v5.addArco(80, &v1);
    v5.addArco(70, &v2);
    v5.addArco(60, &v3);
    v5.addArco(50, &v4);
    v5.addArco(30, &v6);
    v5.addArco(90, &v7);

    v6.addArco(110, &v1);
    v6.addArco(100, &v2);
    v6.addArco(90, &v3);
    v6.addArco(80, &v4);
    v6.addArco(30, &v5);
    v6.addArco(120, &v7);

    v7.addArco(20, &v1);
    v7.addArco(50, &v2);
    v7.addArco(70, &v3);
    v7.addArco(60, &v4);
    v7.addArco(90, &v5);
    v7.addArco(120, &v6);

    //Agregando actividades
    v1.addActividad("Shopping");
    v1.addActividad("Ir al parque");
    v1.addActividad("Ir al Mall");

    v2.addActividad("Termales");
    v2.addActividad("Senderismo");
    v2.addActividad("Canopy");
    v2.addActividad("Observación de aves");
    v2.addActividad("Serpentario");

    v3.addActividad("Senderismo");
    v3.addActividad("Observación de aves");

    v4.addActividad("Senderismo");
    v4.addActividad("Visitar el parque nacional");
    v4.addActividad("Ver el volcan Poas");
    v4.addActividad("Quemaderos");

    v5.addActividad("Ir al Mall");
    v5.addActividad("Ir al parque");
    v5.addActividad("Ir al cine");
    v5.addActividad("Ir al teatro");
    v5.addActividad("Ir al museo");

    v6.addActividad("Ir al Mall");
    v6.addActividad("Ir a la playa");
    v6.addActividad("Ir al zoologico");

    v7.addActividad("Tour de piña");
    v7.addActividad("Campo de Girasoles");

    //-------- Carga de Datos ---------



    //Mostrar las conexiones de cada vertice y mostrarlas
    showVerticeData(&v1);
    showVerticeData(&v2);
    showVerticeData(&v3);
    showVerticeData(&v4);
    showVerticeData(&v5);
    showVerticeData(&v6);
    showVerticeData(&v7);

    return 0;
}


void showVerticeData(Vertice *v){
    cout << "\n--------------------------------------------------------" << endl; 
    cout << "\033[1mDesde " << v->nombre << " se puede ir a:\033[0m " << endl;
    for (auto arco : v->arcos) {
        cout << arco.destino->nombre << ". Distancia: " << arco.distancia << " km." << endl;
    }

    //Mostras actividades de cada vertice
    cout << "\033[1mActividades en " << v->nombre << ":\033[0m " << endl;
    for (auto actividad : v->actividades) {
        cout << actividad << endl;
    }

    cout << "--------------------------------------------------------" << endl; 
}