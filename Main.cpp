#include <iostream>
#include "Estructuras.h"
#include <list>
#include <unordered_map>
#include <vector>
#include <queue>
#include <fstream>

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

Persona::Persona(string genero, int edad, Vertice *origen, Vertice *destino, string actividad) : genero(genero), edad(edad), origen(origen), destino(destino), actividad(actividad) {}


// Prototypes
void cargarDatos();
void registrarActividades();

void showVerticeData(Vertice *vertice);
int calcDistancia(Vertice *origen, Vertice *destino, string ruta, int dis);

void createVertice(string nombre);
void deleteVertice(string nombre);
void modificarVertice(string nombre);

void createArco(string origen, string destino);
void deleteArco(string origen, string destino);
void modificarArco(string origen, string destino);

void showRutaCorta(string origen, string destino, Vertice *listaVertices);
void showActividaesPosibles(string destino, Vertice *listaVertices);
string getActividad(string actividad, Vertice *listaVertices);

void getListaVertices(list<Vertice *> *listaVertices);
Vertice *getVertice(const string &nombre, list<Vertice *> *listaVertices);

void dijkstra(Vertice *inicio, Vertice *destino);

int main()
{
    string origen, destino;
    list<Vertice *> listaVertices;

    //-------- Carga de Datos ---------

    // Creación de vértices
    Vertice v1("Ciudad_Quesada");
    Vertice v2("La_Fortuna");
    Vertice v3("Florencia");
    Vertice v5("San_Jose");
    Vertice v6("Liberia");
    Vertice v7("Pital");
    Vertice v8("Aguas_Zarcas");
    Vertice v9("Zarcero");
    Vertice v10("Muelle");
    Vertice v11("Platanar");
    Vertice v12("Venecia");
    Vertice v13("Rio_Cuarto");

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

    v3.addActividad("Ir al Rio");

    v5.addActividad("Ir al Museo");
    v5.addActividad("Ir al Teatro");
    v5.addActividad("Ir al Mall");

    v6.addActividad("Ir a la playa");
    v6.addActividad("Ir al Mall");

    v7.addActividad("Tour de la piña");
    v7.addActividad("Campo de girasoles");  

    v8.addActividad("Ir al mirador");
    v8.addActividad("Ir a la catarata");
    v8.addActividad("Ir al centro civico");

    v9.addActividad("Ir al parque");
    v9.addActividad("Comprar arboles de navidad");
    v9.addActividad("Ver vacas");

    v10.addActividad("Ir a la gasolinera");

    v11.addActividad("Ir al parque");

    v12.addActividad("Ir al parque");

    v13.addActividad("Ir al parque");
    v13.addActividad("Ir a la laguna");

    // Add vertices to list
    listaVertices.push_back(&v1);
    listaVertices.push_back(&v2);
    listaVertices.push_back(&v3);
    listaVertices.push_back(&v5);
    listaVertices.push_back(&v6);
    listaVertices.push_back(&v7);
    listaVertices.push_back(&v8);
    listaVertices.push_back(&v9);
    listaVertices.push_back(&v10);
    listaVertices.push_back(&v11);
    listaVertices.push_back(&v12);
    listaVertices.push_back(&v13);

    // Show lista
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

    // Show ciudades selected
    cout << origenVertice << endl;
    cout << "Ciudad de partida: " << origenVertice->nombre << endl;
    cout << destinoVertice << endl;
    cout << "Ciudad de destino: " << destinoVertice->nombre << endl;

    int dist = calcDistancia(origenVertice, destinoVertice, " ", 0);
    cout << "\nLa ruta es: " << origenVertice->nombre + "-" + destinoVertice->nombre << "La distancia es: " << dist;

    string actividadEscogida = getActividad("Ir a la playa", destinoVertice);
    cout << "\nLa actividad escogida es: " << actividadEscogida << endl;

    // Construct Persons and add in the binary file

    Persona p1(string("Masculino"), 20, &v1, &v2, string("Ir al parque"));
    Persona p2(string("Femenino"), 30, &v3, &v5, string("Ir al parque"));
    Persona p3(string("Masculino"), 40, &v6, &v7, string("Ir al parque"));
    Persona p4(string("Femenino"), 50, &v8, &v9, string("Ir al parque"));
    Persona p5(string("Masculino"), 60, &v10, &v11, string("Ir al parque"));
    Persona p6(string("Femenino"), 70, &v12, &v13, string("Ir al parque"));

    // Write in the binary file
    ofstream file("persons.bin", ios::binary);
    file.write(reinterpret_cast<char *>(&p1), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p2), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p3), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p4), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p5), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p6), sizeof(Persona));

    file.close();

    // Read from the binary file    
    ifstream file2("persons.bin", ios::binary);
    Persona p = Persona("", 0, nullptr, nullptr, "");

    while (file2.read(reinterpret_cast<char *>(&p), sizeof(Persona))) {
        cout << "\n" << endl;
        cout << "Genero:" << p.genero;
        cout << ", Edad:" << p.edad;
        cout << ", Origen:" << p.origen->nombre;
        cout <<  ", Destino:" << p.destino->nombre;
        cout << ", Actividad:" << p.actividad;
    }
    return 0;
}


int distanciaMenor = 0;
string rutaMenor = "";
int calcDistancia(Vertice *origen, Vertice *destino, string ruta, int dis)
{
    if ((origen == NULL) or (origen->visitado == true))
        return 0;

    if (origen->nombre == destino->nombre)
    {
        if ((distanciaMenor == 0) || (dis < distanciaMenor))
        {
            distanciaMenor = dis;
            rutaMenor = ruta + "-" + destino->nombre;
            // cout << "\nLa ruta es: " << rutaMenor << "La distancia es: " <distanciaMenor;
        }
    }
    origen->visitado = true;

    list<Arco>::iterator tempA = origen->arcos.begin();
    while (tempA != origen->arcos.end())
    {
        calcDistancia(tempA->destino, destino, ruta + origen->nombre, dis + tempA->distancia);
        tempA++;
    }
    origen->visitado = false;
    return distanciaMenor;
}

void getListaVertices(list<Vertice *> *listaVertices)
{
    for (auto vertice : *listaVertices)
    {
        cout << vertice << endl;
        cout << vertice->nombre << endl;
    }
}

Vertice *getVertice(const string &nombre, list<Vertice *> *listaVertices)
{
    for (auto vertice : *listaVertices)
    {
        if (vertice->nombre == nombre)
        {
            cout << vertice << endl;
            return vertice;
        }
    }
    cout << "No se encontro el vertice" << endl;
    return nullptr;
}



string getActividad(string actividad, Vertice *destino)
{
    for (auto act : destino->actividades)
    {
        if (act == actividad)
        {
            return act;
        }
    }
    return "No se encontro la actividad";
}