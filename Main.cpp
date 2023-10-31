#include <iostream>
#include "Estructuras.h"
#include <list>

using namespace std;

Arco::Arco(int dist, Vertice *dest) : distancia(dist), destino(dest) {}

// Implementación del constructor de Vertice
Vertice::Vertice(const string &nombre) : nombre(nombre) {}

// Implementación de la función para agregar actividades
void Vertice::addActividad(const string &actividad)
{
    actividades.push_back(actividad);
}

// Implementación de la función para agregar arcos
void Vertice::addArco(int distancia, Vertice *destino)
{
    // Verificar si el arco ya existe en el vector de arcos
    for (const Arco &arco : arcos)
    {
        if (arco.destino == destino)
        {
            // El arco ya existe, no es necesario agregarlo de nuevo
            return;
        }
    }
    // Agregar el arco si no existe
    arcos.push_back({distancia, destino});
    destino->arcos.push_back({distancia, this});
}

// Prototypes
void cargarDatos();
void registrarActividades();

void showVerticeData(Vertice *vertice);
void calcDistancia(Vertice* origen, Vertice* destino);

void createVertice(string nombre);
void deleteVertice(string nombre);
void modificarVertice(string nombre);

void createArco(string origen, string destino);
void deleteArco(string origen, string destino);
void modificarArco(string origen, string destino);

void showRutaCorta(string origen, string destino, Vertice *listaVertices);
void showActividaesPosibles(string destino, Vertice *listaVertices);
void showListaGlobalActividades();

void getListaVertices(list<Vertice*> *listaVertices);
Vertice* getVertice(const string& nombre, list<Vertice*> *listaVertices);

int main()
{
    string origen, destino;
    list<Vertice*> listaVertices;

    //-------- Carga de Datos ---------

    // Creación de vértices
    Vertice v1("Ciudad Quesada");
    Vertice v2("La Fortuna");
    Vertice v3("Florencia");
    Vertice v4("Zarcero");
    Vertice v5("San Jose");
    Vertice v6("Liberia");
    Vertice v7("Pital");
    Vertice v8("Aguas Zarcas");
    Vertice v9("Zarcero");
    Vertice v10("Muelle");
    Vertice v11("Platanar");
    Vertice v12("Venecia");
    Vertice v13("Rio Cuarto");

    // Conexiones entre vértices (arcos)
    v1.addArco(15, &v3);
    v1.addArco(25, &v8);
    v1.addArco(40, &v9);

    v3.addArco(10, &v11);
    v3.addArco(35, &v2);

    v6.addArco(110, &v2);

    v8.addArco(15, &v7);
    v8.addArco(10, &v12);

    v9.addArco(90, &v5);

    v10.addArco(30, &v2);
    v10.addArco(15, &v11);
    v10.addArco(25, &v7);

    v12.addArco(20, &v7);

    v13.addArco(30, &v12);
    v13.addArco(50, &v7);
    v13.addArco(110, &v5);

    // Agregando actividades
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

    // Mostrar las conexiones de cada vertice y mostrarlas
    // showVerticeData(&v1);
    // showVerticeData(&v2);
    // showVerticeData(&v3);
    // showVerticeData(&v4);
    // showVerticeData(&v5);
    // showVerticeData(&v6);
    // showVerticeData(&v7);
    // showVerticeData(&v8);
    // showVerticeData(&v9);
    // showVerticeData(&v10);
    // showVerticeData(&v11);
    // showVerticeData(&v12);
    // showVerticeData(&v13);

    // Add vertices to list
    listaVertices.push_back(&v1);
    listaVertices.push_back(&v2);
    listaVertices.push_back(&v3);
    listaVertices.push_back(&v4);
    listaVertices.push_back(&v5);
    listaVertices.push_back(&v6);
    listaVertices.push_back(&v7);
    listaVertices.push_back(&v8);
    listaVertices.push_back(&v9);
    listaVertices.push_back(&v10);
    listaVertices.push_back(&v11);
    listaVertices.push_back(&v12);
    listaVertices.push_back(&v13);

    //Show lista
    getListaVertices(&listaVertices);

    string ciudad1, ciudad2;
    cout << "Ingrese el nombre de la ciudad de partida: ";
    cin >> ciudad1;
    cin.ignore();

    cout << "Ingrese el nombre de la ciudad de destino: ";
    cin >> ciudad2;
    cin.ignore();

    Vertice *origenVertice = getVertice(ciudad1, &listaVertices);
    Vertice *destinoVertice = getVertice(ciudad2, &listaVertices);

    //Show ciudades selected
    cout << origenVertice << endl;
    cout << "Ciudad de partida: " << origenVertice->nombre << endl;
    cout << destinoVertice << endl;
    cout << "Ciudad de destino: " << destinoVertice->nombre << endl;

    calcDistancia(origenVertice , destinoVertice);

    // //-------- Menu ---------
    // int opcion = 0;
    // do
    // {
    //     cout << "Menu:" << endl;
    //     cout << "1. Escoger un destino" << endl;
    //     cout << "2. Salir" << endl;
    //     cout << "Ingrese una opcion: ";
    //     cin >> opcion;

    //     switch (opcion)
    //     {
    //     case 1:
    //         cout << "Opcion 1 escogida\n"
    //              << endl;
    //         cout << "Ingrese el nombre del punto de origen: ";
    //         cin >> origen;
    //         cin.ignore();
    //         cout << "Ingrese el nombre de la punto de destino: ";
    //         cin >> destino;
    //         cin.ignore();
    //         showRutaCorta(origen, destino, listaVertices);
    //         break;
    //     case 2:
    //         cout << "Opcion 2" << endl;
    //         break;
    //     case 3:
    //         cout << "Saliendo..." << endl;
    //         break;
    //     default:
    //         cout << "Opcion invalida" << endl;
    //         break;
    //     }
    // } while (opcion != 3);

    return 0;
}

// void showVerticeData(Vertice *v)
// {
//     cout << "\n--------------------------------------------------------" << endl;
//     cout << "Desde " << v->nombre << " se puede ir a: " << endl;
//     for (auto arco : v->arcos)
//     {
//         cout << arco.destino->nombre << ". Distancia: " << arco.distancia << " km." << endl;
//     }

//     // Mostras actividades de cada vertice
//     cout << "Actividades en " << v->nombre << ": " << endl;
//     if (v->actividades.empty())
//     {
//         cout << "No hay actividades disponibles" << endl;
//         return;
//     }
//     for (auto actividad : v->actividades)
//     {
//         cout << actividad << endl;
//     }

//     cout << "--------------------------------------------------------" << endl;
// }

void calcDistancia(Vertice *origen, Vertice *destino)
{
    cout << "Distancia entre " << origen->nombre << " y " << destino->nombre << ": " << endl;
}


void getListaVertices(list<Vertice*> *listaVertices) {
    for (auto vertice : *listaVertices) {
        cout << vertice << endl;
        cout << vertice->nombre << endl;
    }
}

Vertice* getVertice(const string& nombre, list<Vertice*> *listaVertices) {
    for (auto vertice : *listaVertices) {
        if (vertice->nombre == nombre) {
            cout << vertice << endl;
            return vertice;
        }
    }
    cout << "No se encontro el vertice" << endl;
    return nullptr;
}


// void showRutaCorta(string origen, string destino, list<Vertice> *listaVertices)
// {
//     // Search for the vertex with the given name
//     Vertice *origenVertice = getVertice(origen, &listaVertices);
//     Vertice *destinoVertice = getVertice(destino, listaVertices);

//     // Calculate the distance between the two vertices
//     calcDistancia(origenVertice, destinoVertice);

//     // Show the possible activities in the destination vertex
//     showActividaesPosibles(destino, listaVertices);
// }

// void showActividaesPosibles(string destino, list<Vertice> *listaVertices)
// {
//     // Search for the vertex with the given name
//     Vertice *destinoVertice = getVertice(destino, *listaVertices);

//     // Show the possible activities in the destination vertex
//     cout << "Actividades en " << destinoVertice->nombre << ": " << endl;
//     for (auto actividad : destinoVertice->actividades)
//     {
//         cout << actividad << endl;
//     }
// }