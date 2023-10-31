#include <iostream>
#include "Estructuras.h"

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
void calcDistancia(Vertice *orige, Vertice *destino);
void logUser();

void createVertice(string nombre);
void deleteVertice(string nombre);
void modificarVertice(string nombre);

void createArco(string origen, string destino);
void deleteArco(string origen, string destino);
void modificarArco(string origen, string destino);

void showRutaCorta(string origen, string destino, Vertice *listaVertices);
void showActividaesPosibles(string destino, Vertice *listaVertices);
void showListaGlobalActividades();

int main()
{
    string origen, destino;
    // Vertice lsit
    Vertice *listaVertices = nullptr;

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
    showVerticeData(&v1);
    showVerticeData(&v2);
    showVerticeData(&v3);
    showVerticeData(&v4);
    showVerticeData(&v5);
    showVerticeData(&v6);
    showVerticeData(&v7);
    showVerticeData(&v8);
    showVerticeData(&v9);
    showVerticeData(&v10);
    showVerticeData(&v11);
    showVerticeData(&v12);
    showVerticeData(&v13);

    // Add vertices to list
    listaVertices = &v1;

    //-------- Menu ---------
    int opcion = 0;
    do
    {
        cout << "Menu:" << endl;
        cout << "1. Escoger un destino" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Opcion 1 escogida\n"
                 << endl;
            cout << "Ingrese el nombre del punto de origen: ";
            cin >> origen;
            cin.ignore();
            cout << "Ingrese el nombre de la punto de destino: ";
            cin >> destino;
            cin.ignore();
            showRutaCorta(origen, destino, listaVertices);
            break;
        case 2:
            cout << "Opcion 2" << endl;
            break;
        case 3:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion invalida" << endl;
            break;
        }
    } while (opcion != 3);

    return 0;
}

void showVerticeData(Vertice *v)
{
    cout << "\n--------------------------------------------------------" << endl;
    cout << "Desde " << v->nombre << " se puede ir a: " << endl;
    for (auto arco : v->arcos)
    {
        cout << arco.destino->nombre << ". Distancia: " << arco.distancia << " km." << endl;
    }

    // Mostras actividades de cada vertice
    cout << "Actividades en " << v->nombre << ": " << endl;
    if (v->actividades.empty())
    {
        cout << "No hay actividades disponibles" << endl;
        return;
    }
    for (auto actividad : v->actividades)
    {
        cout << actividad << endl;
    }

    cout << "--------------------------------------------------------" << endl;
}

void calcDistancia(Vertice *origen, Vertice *destino)
{
    cout << "Distancia entre " << origen->nombre << " y " << destino->nombre << ": " << endl;
}

Vertice *getVertice(string nombre, Vertice *listaVertices)
{
    Vertice *verticeActual = listaVertices;
    cout << "Buscando vertice con nombre: " << endl;
    // Move using arcos
    for (auto var : verticeActual->arcos)
    {
        cout << var.destino->nombre << endl;
        if (var.destino->nombre == nombre)
        {
            return var.destino;
        }
    }

    // Si no se encontró el vértice, devuelve nullptr
    cout << "Vertice no encontrado (NO colinda con el punto de salida)" << endl;
    return nullptr;
}

void logUser()
{
}

void showRutaCorta(string origen, string destino, Vertice *listaVertices)
{
    // Search for the vertex with the given name
    Vertice *origenVertice = getVertice(origen, listaVertices);
    Vertice *destinoVertice = getVertice(destino, listaVertices);

    // Calculate the distance between the two vertices
    calcDistancia(origenVertice, destinoVertice);

    // Show the possible activities in the destination vertex
    showActividaesPosibles(destino, listaVertices);
}

void showActividaesPosibles(string destino, Vertice *listaVertices)
{
    // Search for the vertex with the given name
    Vertice *destinoVertice = getVertice(destino, listaVertices);

    // Show the possible activities in the destination vertex
    cout << "Actividades en " << destinoVertice->nombre << ": " << endl;
    for (auto actividad : destinoVertice->actividades)
    {
        cout << actividad << endl;
    }
}