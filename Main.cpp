#include <iostream>
#include "Estructuras.h"
#include <list>
#include <unordered_map>
#include <vector>
#include <queue>
#include <fstream>
#include "fstream"
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

std::list<Vertice> listaVertices;
std::list<string> listaActividades;

Arco::Arco(int dist, Vertice *dest) : distancia(dist), destino(dest) {}

// Implementación del constructor de Vertice
Vertice::Vertice(const string nombre) : nombre(nombre) {}

// Implementación de la función para agregar actividades
void Vertice::addActividad(const std::string &actividad)
{
    auto it = std::find(listaActividades.begin(), listaActividades.end(), actividad);

    if (it != listaActividades.end())
    {
        actividades.push_back(&(*it));
    }
    else
    {
        std::cout << "La actividad '" << actividad << "' no está en la lista global. No se puede agregar al vértice." << std::endl;
    }
}

void Vertice::addArco(int distancia, string inicio, string destino)
{
    Vertice *origen = nullptr;

    for (auto &vertice : listaVertices)
    {
        if (vertice.nombre == inicio)
        {
            origen = &vertice;
            break;
        }
    }

    if (origen == nullptr)
    {
        cout << "No se encontró el vértice de origen al que se le desea agregar la conexion (Origen)" << endl;
        return;
    }

    Vertice *dest = nullptr;

    if (listaVertices.empty())
    {
        cout << "No hay vertices dentro de la lista vertices" << endl;
        return;
    }

    for (auto &vertice : listaVertices)
    {
        cout << vertice.nombre << endl;
        if (vertice.nombre == destino)
        {
            dest = &vertice;
            break;
        }
    }

    if (dest == nullptr)
    {
        cout << "No se encontró el vértice de destino al que se le desea agregar la conexion (Destino)" << endl;
        return;
    }

    if (origen == dest)
    {
        cout << "No se puede agregar una conexion al mismo vértice" << endl;
        return;
    }

    Arco arco = Arco(distancia, dest);
    origen->arcos.push_back(arco);
    cout << "Se agregó la conexion correctamente de " << origen->nombre << " a " << dest->nombre << endl;
}

struct Persona
{
    char genero;
    int edad;
    char origen[15];
    char destino[15];
    char actividad[30];

    Persona(char genero, int edad, const char origen[15], const char destino[15], const char actividad[30]);
};

Persona::Persona(char genero, int edad, const char origen1[15], const char destino1[15], const char actividad1[30])
    : genero(genero), edad(edad)
{
    strcpy(origen, origen1);
    strcpy(destino, destino1);
    strcpy(actividad, actividad1);
}

struct Nodo
{
    list<Persona> lista;
    Nodo *left;
    Nodo *right;

    Nodo(list<Persona> lista)
    {
        this->lista = lista;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// Prototypes
void cargarDatos();
void registrarActividades();

void showVerticeData(Vertice vertice);

void createVertice(list<Vertice *> &vertices, const string nombreV);
void eliminarVertice(std::list<Vertice> &listaVertices, const Vertice &vertice);
void modificarVertice(Vertice *vertice, string &nuevoNombre);

void createArco(string origen, string destino);
void deleteArco(Vertice &vertice, const string &nombreDestino);
void modificarArco(Vertice &vertice, string &nombreDestino, int nuevaDistancia, Vertice &nuevoDestino);

void showRutaCorta(string origen, string destino, Vertice listaVertices);
void showActividaesPosibles(string destino, Vertice listaVertices);
string getActividad(string actividad, Vertice listaVertices);

void getListaVertices(list<Vertice> listaVertices);
Vertice getVertice(const string &nombre, list<Vertice> listaVertices);

Arco getArco(Vertice &vertice, const string &nombreDestino);

void getListaActividades(list<string> listaActividades);
void actividadesVertice(const std::list<Vertice> &vertices);

void calcRutaCorta(string origen, string destino);
void encontrarRuta(Vertice *origen, Vertice *destino, std::vector<Vertice *> &listaRutaVertices, std::vector<std::vector<Vertice *>> &listaRutaTodosVertices, std::vector<int> &listaDistancias, int distanciaTotal);

void amplitud(Vertice *inicio);
void profundidad(Vertice *inicio);
void profundidadRecursivo(Vertice *actual, std::list<Vertice *> &visitados);

void agregarPersona();

void cargarDatos()
{
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

    // Agregar actividades a lista global
    listaActividades.push_back("Shopping");
    listaActividades.push_back("Ir al parque");
    listaActividades.push_back("Ir al Mall");
    listaActividades.push_back("Termales");
    listaActividades.push_back("Senderismo");
    listaActividades.push_back("Canopy");
    listaActividades.push_back("Observación de aves");
    listaActividades.push_back("Serpentario");
    listaActividades.push_back("Ir al cine");
    listaActividades.push_back("Ir al teatro");
    listaActividades.push_back("Ir al museo");
    listaActividades.push_back("Ir a la playa");
    listaActividades.push_back("Ir al zoologico");
    listaActividades.push_back("Tour de piña");
    listaActividades.push_back("Campo de Girasoles");
    listaActividades.push_back("Ir al mirador");
    listaActividades.push_back("Ir a la catarata");
    listaActividades.push_back("Ir al centro civico");
    listaActividades.push_back("Comprar arboles de navidad");
    listaActividades.push_back("Ver vacas");
    listaActividades.push_back("Ir a la gasolinera");
    listaActividades.push_back("Ir a la laguna");

    // Agregando actividades a vertices
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
    listaVertices.push_back(v1);
    listaVertices.push_back(v2);
    listaVertices.push_back(v3);
    listaVertices.push_back(v5);
    listaVertices.push_back(v6);
    listaVertices.push_back(v7);
    listaVertices.push_back(v8);
    listaVertices.push_back(v9);
    listaVertices.push_back(v10);
    listaVertices.push_back(v11);
    listaVertices.push_back(v12);
    listaVertices.push_back(v13);

    // Conexiones entre vértices (arcos)
    v1.addArco(15, "Ciudad_Quesada", "Florencia");
    v1.addArco(25, "Ciudad_Quesada", "Aguas_Zarcas");
    v1.addArco(40, "Ciudad_Quesada", "Zarcero");

    v2.addArco(35, "La_Fortuna", "Florencia");
    v2.addArco(110, "La_Fortuna", "Liberia");
    v2.addArco(30, "La_Fortuna", "Muelle");

    v3.addArco(15, "Florencia", "Ciudad_Quesada");
    v3.addArco(10, "Florencia", "Platanar");
    v3.addArco(35, "Florencia", "La_Fortuna");

    v5.addArco(90, "San_Jose", "Zarcero");
    v5.addArco(110, "San_Jose", "Rio_Cuarto");

    v6.addArco(110, "Liberia", "La_Fortuna");

    v7.addArco(15, "Pital", "Aguas_Zarcas");
    v7.addArco(25, "Pital", "Muelle");
    v7.addArco(20, "Pital", "Venecia");
    v7.addArco(50, "Pital", "Rio_Cuarto");

    v8.addArco(25, "Aguas_Zarcas", "Ciudad_Quesada");
    v8.addArco(15, "Aguas_Zarcas", "Pital");
    v8.addArco(10, "Aguas_Zarcas", "Venecia");

    v9.addArco(40, "Zarcero", "Ciudad_Quesada");
    v9.addArco(90, "Zarcero", "San_Jose");

    v10.addArco(30, "Muelle", "La_Fortuna");
    v10.addArco(15, "Muelle", "Platanar");
    v10.addArco(25, "Muelle", "Pital");

    v11.addArco(10, "Platanar", "Florencia");
    v11.addArco(15, "Platanar", "Muelle");

    v12.addArco(20, "Venecia", "Pital");
    v12.addArco(10, "Venecia", "Aguas_Zarcas");
    v12.addArco(30, "Venecia", "Rio_Cuarto");

    v13.addArco(30, "Rio_Cuarto", "Venecia");
    v13.addArco(50, "Rio_Cuarto", "Pital");
    v13.addArco(110, "Rio_Cuarto", "San_Jose");

    // Construct Persons and add in the binary file

    Persona p1('M', 20, "Ciudad_Quesada", "La_Fortuna", "Ir al parque");
    Persona p2('F', 30, (v3.nombre.c_str()), (v5.nombre.c_str()), "Ir al parque");
    Persona p3('M', 40, v6.nombre.c_str(), v7.nombre.c_str(), ("Ir al parque"));
    Persona p4('F', 50, v8.nombre.c_str(), v9.nombre.c_str(), ("Ir al parque"));
    Persona p5('M', 60, v10.nombre.c_str(), v11.nombre.c_str(), ("Ir al parque"));
    Persona p6('F', 70, v12.nombre.c_str(), v13.nombre.c_str(), ("Ir al parque"));
    Persona p7('M', 18, v1.nombre.c_str(), v2.nombre.c_str(), ("Ir al parque"));
    Persona p8('F', 19, v3.nombre.c_str(), v7.nombre.c_str(), ("Ir al parque"));
    Persona p9('M', 20, v5.nombre.c_str(), v6.nombre.c_str(), ("Ir al parque"));
    Persona p10('F', 21, v7.nombre.c_str(), v8.nombre.c_str(), ("Ir al parque"));
    Persona p11('F', 16, v9.nombre.c_str(), v10.nombre.c_str(), ("Ir al parque"));
    Persona p12('M', 17, v11.nombre.c_str(), v12.nombre.c_str(), ("Ir al parque"));
    Persona p13('F', 18, v13.nombre.c_str(), v1.nombre.c_str(), ("Ir al parque"));
    Persona p14('M', 23, v2.nombre.c_str(), v3.nombre.c_str(), ("Ir al parque"));
    Persona p15('F', 24, v7.nombre.c_str(), v5.nombre.c_str(), ("Ir al parque"));
    Persona p16('M', 25, v6.nombre.c_str(), v7.nombre.c_str(), ("Ir al parque"));
    Persona p17('F', 19, v8.nombre.c_str(), v9.nombre.c_str(), ("Ir al parque"));
    Persona p18('M', 20, v10.nombre.c_str(), v11.nombre.c_str(), ("Ir al parque"));
    Persona p19('F', 21, v12.nombre.c_str(), v13.nombre.c_str(), ("Ir al parque"));
    Persona p20('M', 22, v1.nombre.c_str(), v2.nombre.c_str(), ("Ir al parque"));
    Persona p21('F', 23, v3.nombre.c_str(), v7.nombre.c_str(), ("Ir al parque"));
    Persona p22('M', 13, v5.nombre.c_str(), v6.nombre.c_str(), ("Ir al parque"));
    Persona p23('F', 14, v7.nombre.c_str(), v8.nombre.c_str(), ("Ir al parque"));
    Persona p24('M', 15, v9.nombre.c_str(), v10.nombre.c_str(), ("Ir al parque"));
    Persona p25('F', 16, v11.nombre.c_str(), v12.nombre.c_str(), ("Ir al parque"));
    Persona p26('M', 17, v13.nombre.c_str(), v1.nombre.c_str(), ("Ir al parque"));
    Persona p27('F', 18, v2.nombre.c_str(), v3.nombre.c_str(), ("Ir al parque"));
    Persona p28('M', 19, v7.nombre.c_str(), v5.nombre.c_str(), ("Ir al parque"));
    Persona p29('F', 20, v6.nombre.c_str(), v7.nombre.c_str(), ("Ir al parque"));
    Persona p30('M', 21, v8.nombre.c_str(), v9.nombre.c_str(), ("Ir al parque"));

    // Write in the binary file

    fstream file("persons.bin", ios::in | ios::out | ios::binary | ios::trunc);

    file.write(reinterpret_cast<char *>(&p1), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p2), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p3), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p4), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p5), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p6), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p7), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p8), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p9), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p10), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p11), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p12), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p13), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p14), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p15), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p16), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p17), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p18), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p19), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p20), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p21), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p22), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p23), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p24), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p25), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p26), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p27), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p28), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p29), sizeof(Persona));
    file.write(reinterpret_cast<char *>(&p30), sizeof(Persona));

    file.close();
}

void leerArchivo()
{
    // Read from the binary file
    // ifstream file2("persons.bin", ios::binary);
    fstream file2("persons.bin", ios::in | ios::out | ios::binary);
    //
    Persona p = Persona('z', 0, "", "", "");
    file2.read(reinterpret_cast<char *>(&p), sizeof(Persona));

    while (!file2.eof())
    {
        cout << "\n"
             << endl;
        if (p.genero == 'M')
            cout << "hombre de ";
        else
            cout << "mujer de";

        cout << " " << p.edad;
        cout << " años está en " << p.origen;
        cout << " y quiere viajar a " << p.destino;
        cout << " para " << p.actividad;
        file2.read(reinterpret_cast<char *>(&p), sizeof(p));
    }
}

// Verificar si el numero ya existe en el array
bool insideArray(list<int> array, int num)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (array.front() == num)
        {
            cout << "El numero ya existe" << endl;
            return true;
        }
        array.pop_front();
    }
    return false;
}

// Crear el arbol binario en base a la lista de personas y el orden que el usuario escoga
void createTree(list<Persona> listaPersonas)
{
    // Crear el nodo raíz con la lista de personas
    Nodo *root = new Nodo(listaPersonas);

    // Solictar el orden al usuario
    list<int> orden;
    int num;
    cout << "Ingrese el orden de los datos: " << endl;
    cout << "1. Genero" << endl;
    cout << "2. Edad" << endl;
    cout << "3. Origen" << endl;
    cout << "4. Actividad" << endl;

    for (int i = 0; i < 4; i++)
    {
        do
        {
            cin >> num;
        } while (insideArray(orden, num));
        orden.push_back(num);
    }

    list<int> ordenTmp = orden;
    // Print order
    cout << "\nEl escogido orden es: " << endl;
    for (int i = 0; i < 4; i++)
    {
        if (ordenTmp.front() == 1)
            cout << i + 1 << ". Genero" << endl;
        else if (ordenTmp.front() == 2)
            cout << i + 1 << ". Edad" << endl;
        else if (ordenTmp.front() == 3)
            cout << i + 1 << ". Origen" << endl;
        else if (ordenTmp.front() == 4)
            cout << i + 1 << ". Actividad" << endl;
        ordenTmp.pop_front();
    }

    list<int> ordenTmp2 = orden;

    list<Persona> listaHombres;
    list<Persona> listaMujeres;
    list<Persona> lista18_30;
    list<Persona> lista31_64;
    list<Persona> lista65;
    list<Persona> listav1;
    list<Persona> listav2;
    list<Persona> listav3;
    list<Persona> listav4;
    list<Persona> listav5;
    list<Persona> listav6;
    list<Persona> listav7;
    list<Persona> listav8;
    list<Persona> listav9;
    list<Persona> listav10;
    list<Persona> listav11;
    list<Persona> listav12;
    list<Persona> listav13;
    list<Persona> listaShopping;
    list<Persona> listaParque;
    list<Persona> listaMall;
    list<Persona> listaTermales;
    list<Persona> listaSenderismo;
    list<Persona> listaCanopy;
    list<Persona> listaAves;
    list<Persona> listaZoo;
    list<Persona> listaPlaya;
    list<Persona> listaMuseo;
    list<Persona> listaTeatro;
    list<Persona> listaCine;
    list<Persona> listaSerpentario;
    list<Persona> listaPina;
    list<Persona> listaGirasoles;
    list<Persona> listaLaguna;
    list<Persona> listaNavidad;
    for (int i = 0; i < 4; i++)
    {
        if (ordenTmp2.front() == 1)
        {
            // Ordenar por genero
            list<Persona> listaTmp = root->lista;
            while (!listaTmp.empty())
            {
                if (listaTmp.front().genero == 'M')
                {
                    listaHombres.push_back(listaTmp.front());
                }
                else
                {
                    listaMujeres.push_back(listaTmp.front());
                }
                listaTmp.pop_front();
            }
        }
        else if (ordenTmp2.front() == 2)
        {
            // Ordenar por edad
            list<Persona> listaTmp = root->lista;
            while (!listaTmp.empty())
            {
                if (listaTmp.front().edad >= 18 && listaTmp.front().edad <= 30)
                    lista18_30.push_back(listaTmp.front());
                else if (listaTmp.front().edad >= 31 && listaTmp.front().edad <= 64)
                    lista31_64.push_back(listaTmp.front());
                else
                    lista65.push_back(listaTmp.front());
                listaTmp.pop_front();
            }
        }
        else if (ordenTmp2.front() == 3)
        {
            // Ordenar por origen

            list<Persona> listaTmp = root->lista;
            while (!listaTmp.empty())
            {
                if (string(listaTmp.front().origen) == "Ciudad_Quesada")
                    listav1.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "La_Fortuna")
                    listav2.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "Florencia")
                    listav3.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "San_Jose")
                    listav5.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "Liberia")
                    listav6.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "Pital")
                    listav7.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "Aguas_Zarcas")
                    listav8.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "Zarcero")
                    listav9.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "Muelle")
                    listav10.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "Platanar")
                    listav11.push_back(listaTmp.front());

                else if (string(listaTmp.front().origen) == "Venecia")
                    listav12.push_back(listaTmp.front());
                else
                    listav13.push_back(listaTmp.front());
                listaTmp.pop_front();
            }
        }
        else if (ordenTmp2.front() == 4)
        {
            // Ordenar por actividad
            list<Persona> listaTmp = root->lista;
            while (!listaTmp.empty())
            {
                if (string(listaTmp.front().actividad) == "Shopping")
                    listaShopping.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Ir al parque")
                    listaParque.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Ir al Mall")
                    listaMall.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Termales")
                    listaTermales.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Senderismo")
                    listaSenderismo.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Canopy")
                    listaCanopy.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Observacion de aves")
                    listaAves.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Ir al zoologico")
                    listaZoo.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Ir a la playa")
                    listaPlaya.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Ir al museo")
                    listaMuseo.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Ir al teatro")
                    listaTeatro.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Ir al cine")
                    listaCine.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Serpentario")
                    listaSerpentario.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Tour de piña")
                    listaPina.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Campo de girasoles")
                    listaGirasoles.push_back(listaTmp.front());

                else if (string(listaTmp.front().actividad) == "Ir a la laguna")
                    listaLaguna.push_back(listaTmp.front());
                else
                    listaNavidad.push_back(listaTmp.front());
                listaTmp.pop_front();
            }
        }
        ordenTmp2.pop_front();
    }

    // Mostrar el arbol por niveles
    cout << "\n\nMostrando el arbol por niveles: " << endl;
    queue<Nodo *> cola;
    cola.push(root);

    while (!cola.empty())
    {
        Nodo *tmp = cola.front();
        cola.pop();

        cout << "\nNiveles: " << endl;

        list<int> ordenTmp = orden;
        while (!ordenTmp.empty())
        {
            if (ordenTmp.front() == 1)
            {
                cout << "\n--------------------GENERO---------------------" << endl;
                cout << "Cantidad de hombres: " << listaHombres.size() << endl;
                cout << "Cantidad de mujeres: " << listaMujeres.size() << endl;
            }
            else if (ordenTmp.front() == 2)
            {
                cout << "\n--------------------EDAD--------------------" << endl;
                cout << "Cantidad de personas de 18 a 30 años: " << lista18_30.size() << endl;
                cout << "Cantidad de personas de 31 a 64 años: " << lista31_64.size() << endl;
                cout << "Cantidad de personas de 65 años en adelante: " << lista65.size() << endl;
            }
            else if (ordenTmp.front() == 3)
            {
                cout << "\n------------------ORIGEN--------------------" << endl;
                cout << "Cantidad de personas en Ciudad_Quesada: " << listav1.size() << endl;
                cout << "Cantidad de personas en La_Fortuna: " << listav2.size() << endl;
                cout << "Cantidad de personas en Florencia: " << listav3.size() << endl;
                cout << "Cantidad de personas en San Jose: " << listav5.size() << endl;
                cout << "Cantidad de personas en Liberia: " << listav6.size() << endl;
                cout << "Cantidad de personas en Pital: " << listav7.size() << endl;
                cout << "Cantidad de personas en Aguas Zarcas: " << listav8.size() << endl;
                cout << "Cantidad de personas en Zarcero: " << listav9.size() << endl;
                cout << "Cantidad de personas en Muelle: " << listav10.size() << endl;
                cout << "Cantidad de personas en Platanar: " << listav11.size() << endl;
                cout << "Cantidad de personas en Venecia: " << listav12.size() << endl;
                cout << "Cantidad de personas en Rio Cuarto: " << listav13.size() << endl;
            }
            else if (ordenTmp.front() == 4)
            {
                cout << "\n--------------------ACTIVIDAD--------------------" << endl;
                cout << "Cantidad de personas que hacen Shopping: " << listaShopping.size() << endl;
                cout << "Cantidad de personas que van al parque: " << listaParque.size() << endl;
                cout << "Cantidad de personas que van al Mall: " << listaMall.size() << endl;
                cout << "Cantidad de personas que van a las termales: " << listaTermales.size() << endl;
                cout << "Cantidad de personas que hacen Senderismo: " << listaSenderismo.size() << endl;
                cout << "Cantidad de personas que hacen Canopy: " << listaCanopy.size() << endl;
                cout << "Cantidad de personas que van  observar aves: " << listaAves.size() << endl;
                cout << "Cantidad de personas que van al zoologico: " << listaZoo.size() << endl;
                cout << "Cantidad de personas que van a la playa: " << listaPlaya.size() << endl;
                cout << "Cantidad de personas que van al museo: " << listaMuseo.size() << endl;
                cout << "Cantidad de personas que van al teatro: " << listaTeatro.size() << endl;
                cout << "Cantidad de personas que van al cine: " << listaCine.size() << endl;
                cout << "Cantidad de personas que van al serpentario: " << listaSerpentario.size() << endl;
                cout << "Cantidad de personas que van al Tour de piña: " << listaPina.size() << endl;
                cout << "Cantidad de personas que van al campo de girasoles: " << listaGirasoles.size() << endl;
                cout << "Cantidad de personas que van a la laguna: " << listaLaguna.size() << endl;
                cout << "Cantidad de personas que van a comprar arboles de Navidad: " << listaNavidad.size() << endl;
            }

            ordenTmp.pop_front();
        }

        if (tmp->left != nullptr)
            cola.push(tmp->left);
        if (tmp->right != nullptr)
            cola.push(tmp->right);
    }
}

// Crear arreglo con los datos de las personas para el arbol
void displayTree()
{
    fstream file2("persons.bin", ios::in | ios::out | ios::binary);
    Persona p = Persona('z', 0, "", "", "");
    file2.read(reinterpret_cast<char *>(&p), sizeof(Persona));
    // Lista de personas
    list<Persona> listaPersonas;

    while (!file2.eof())
    {
        listaPersonas.push_back(p);
        file2.read(reinterpret_cast<char *>(&p), sizeof(p));
    }

    createTree(listaPersonas);
}

// Fucion para calculae el porcentaje de personas por genero en una ciudad
int totalH = 0;
int totalM = 0;
int porcH = 0;
int porcM = 0;
int cantH = 0;
int cantM = 0;
int totalP = 0;
void calcPorcentaje(Vertice vertice)
{
    fstream file2("persons.bin", ios::in | ios::out | ios::binary);
    Persona p = Persona('z', 0, "", "", "");
    file2.read(reinterpret_cast<char *>(&p), sizeof(Persona));
    // Lista de personas
    list<Persona> listaPersonas;

    while (!file2.eof())
    {
        listaPersonas.push_back(p);
        file2.read(reinterpret_cast<char *>(&p), sizeof(p));
    }

    Nodo *raiz = new Nodo(listaPersonas);
    list<Persona> listaHombres;
    list<Persona> listaMujeres;
    list<Persona> listaTmp = raiz->lista;
    while (!listaTmp.empty())
    {
        if (listaTmp.front().genero == 'M')
            listaHombres.push_back(listaTmp.front());
        else
            listaMujeres.push_back(listaTmp.front());
        listaTmp.pop_front();
    }

    for (auto hombre : listaHombres)
    {
        totalH++;
        if (string(hombre.origen) == vertice.nombre)
        {
            cantH++;
        }
    }

    for (auto mujer : listaMujeres)
    {
        totalM++;
        if (string(mujer.origen) == vertice.nombre)
        {
            cantM++;
        }
    }

    totalP = totalH + totalM;
    porcH = (totalH * 100) / totalP;
    porcM = (totalM * 100) / totalP;

    cout << "\nPorcentaje de mujeres registardas: " << porcM << "%" << endl;
    cout << "Porcentaje de hombres registardos: " << porcH << "%" << endl;

    porcH = (cantH * 100) / totalH;
    porcM = (cantM * 100) / totalM;
    cout << "\nPorcentaje de personas en " << vertice.nombre << endl;
    cout << "\nPorcentaje de mujeres: " << porcM << "%" << endl;
    cout << "Porcentaje de hombres: " << porcH << "%" << endl;
}

// Menu
void menu()
{
    cout << "\n1. Menu Personas";
    cout << "\n2. Menu Ciudades";
    cout << "\n3. Menu Rutas";
    cout << "\n4. Menu Actividades";
    cout << "\n0. Salir \n";
    cout << ">";
}
void menuPersonas()
{
    cout << "\n1. Leer Archivo";
    cout << "\n2. Consultar Personas";
    cout << "\n3. Consultar porcentaje por provincia";
    cout << "\n4. Agregar Persona";
    cout << "\n0. Salir \n";
    cout << ">";
}
void menuCiudades()
{
    cout << "\n1. Mostrar Vertices";
    cout << "\n2. Añadir Ciudad";
    cout << "\n3. Modificar Ciudad";
    cout << "\n4. Eliminar Ciudad";
    cout << "\n0. Salir \n";
    cout << ">";
}
void menuRutas()
{
    cout << "\n1. Ruta corta";
    cout << "\n2. Crear ruta";
    cout << "\n3. Modificar ruta";
    cout << "\n4. Eliminar ruta";
    cout << "\n0. Salir \n";
    cout << ">";
}
void menuActividad()
{
    cout << "\n1. Mostrar todas las actividades";
    cout << "\n2. Mostrar actividad por vertice";
    cout << "\n0. Salir\n>";
}

int main()
{

    string origen, destino;

    cargarDatos();

    int opcion;
    while (true)
    {
        menu();
        cin >> opcion;

        if (opcion == 1)
        {
            int opcionPersona;
            while (true)
            {
                menuPersonas();
                cin >> opcionPersona;
                if (opcionPersona == 1)
                {
                    leerArchivo();
                    cout << "\n \nArchivo leido \n \n";
                }
                else if (opcionPersona == 2)
                {
                    cout << "Desplegando valores con el arbol binario: \n \n";
                    displayTree();
                }
                else if (opcionPersona == 3)
                {
                    int totalH = 0;
                    int totalM = 0;
                    int porcH = 0;
                    int porcM = 0;
                    int cantH = 0;
                    int cantM = 0;
                    string vert;
                    cout << "Ingrese el nombre del vertice que desea consultar: ";
                    cin >> vert;
                    cin.ignore();
                    Vertice ConsVert = getVertice(vert, listaVertices);
                    if (ConsVert.nombre != "")
                        calcPorcentaje(ConsVert);
                    else
                        cout << "No se encontró el vertice" << endl;
                }
                else if (opcionPersona == 4)
                {
                    agregarPersona();
                }
                else if (opcionPersona == 0)
                    break;
            }
        }
        else if (opcion == 2)
        {
            int opcionCiudad;
            while (true)
            {
                menuCiudades();
                cin >> opcionCiudad;
                if (opcionCiudad == 1)
                {
                    getListaVertices(listaVertices);
                }
                else if (opcionCiudad == 2)
                {
                    string nombreVertice;
                    cout << "\nIngrese el nombre de la nueva ciudad: ";
                    cin >> nombreVertice;
                    Vertice v = Vertice(nombreVertice);
                    listaVertices.push_back(v);
                    cin.ignore();
                }
                else if (opcionCiudad == 3)
                {
                    string nombreVertice, nuevoNombre;
                    cout << "\nIngrese el nombre de la ciudad: ";
                    cin >> nombreVertice;
                    cin.ignore();
                    Vertice modVertice = getVertice(nombreVertice, listaVertices);
                    if (modVertice.nombre == nombreVertice)
                    {
                        cout << "\nIngrese el nuevo nombre para la ciudad: ";
                        cin >> nuevoNombre;
                        cin.ignore();
                        // modificarVertice(modVertice, nuevoNombre);
                    }
                    else
                    {
                        cout << "El vértice no se encontró en la lista." << endl;
                    }
                }
                else if (opcionCiudad == 4)
                {
                    string origenArco, nDestino;
                    cout << "\nIngrese el nombre de la ciudad a borrar: ";
                    cin >> origenArco;
                    cin.ignore();
                    Vertice origenVertice = getVertice(origenArco, listaVertices);
                    eliminarVertice(listaVertices, origenVertice);
                    cout << "Vertice borrado con éxito!";
                }
                else if (opcionCiudad == 0)
                    break;
            }
        }

        else if (opcion == 3)
        {
            int opcionRuta;
            while (true)
            {
                menuRutas();
                cin >> opcionRuta;
                if (opcionRuta == 1)
                {
                    cout << "Ingrese el nombre de la ciudad de partida: ";
                    cin >> origen;
                    cin.ignore();

                    cout << "Ingrese el nombre de la ciudad de destino: ";
                    cin >> destino;
                    cin.ignore();

                    Vertice origenVertice = getVertice(origen, listaVertices);
                    Vertice destinoVertice = getVertice(destino, listaVertices);

                    cout << "Ciudad de partida: " << origenVertice.nombre << endl;
                    cout << "Ciudad de destino: " << destinoVertice.nombre << endl;
                    // int distanciaMenor = 0;
                    // int dist = calcDistancia(origenVertice, destinoVertice, " ", 0);
                    // cout << "\nLa ruta es: " << origen + "-" + destino << ", La distancia es: " << dist;
                    calcRutaCorta(origen, destino);
                }
                else if (opcionRuta == 2)
                {
                    string nOrigen, nDestino;
                    int dist;
                    cout << "\nIngrese el nombre de la ciudad de origen: ";
                    cin >> nOrigen;
                    cin.ignore();
                    Vertice origenVertice = getVertice(nOrigen, listaVertices);
                    cout << "\nIngrese el nombre de la ciudad destino: ";
                    cin >> nDestino;
                    cin.ignore();
                    Vertice destinoVertice = getVertice(nDestino, listaVertices);
                    cout << "\nDigite la distancia entre el origen y el destino: ";
                    cin >> dist;
                    cin.ignore();
                    origenVertice.addArco(dist, nOrigen, nDestino);
                    destinoVertice.addArco(dist, nDestino, nOrigen);
                    cout << "Ruta creada con éxito!";
                }
                else if (opcionRuta == 3)
                {
                    string nOrigen, nDestino, nuevoDestino;
                    int nDist;
                    cout << "\nIngrese el nombre de la ciudad de origen: ";
                    cin >> nOrigen;
                    cin.ignore();
                    Vertice origenVertice = getVertice(nOrigen, listaVertices);
                    cout << "\nIngrese el nombre de la ciudad destino: ";
                    cin >> nDestino;
                    cin.ignore();
                    cout << "\nIngrese el nombre de la nueva ciudad de destino: ";
                    cin >> nuevoDestino;
                    cin.ignore();
                    Vertice destinoArco = getVertice(nOrigen, listaVertices);
                    cout << "\nIngrese la distancia de la ruta: ";
                    cin >> nDist;
                    cin.ignore();
                }
                else if (opcionRuta == 4)
                {
                    string origenArco, nDestino;
                    cout << "\nIngrese el nombre de la ciudad a borrar: ";
                    cin >> origenArco;
                    cin.ignore();
                    Vertice origenVertice = getVertice(origenArco, listaVertices);
                    eliminarVertice(listaVertices, origenVertice);
                    cout << "Vertice borrado con éxito!";
                }
                else if (opcionRuta == 0)
                    break;
            }
        }
        else if (opcion == 4)
        {
            int opcionAct;
            while (true)
            {
                menuActividad();
                cin >> opcionAct;
                if (opcionAct == 1)
                    getListaActividades(listaActividades);
                else if (opcionAct == 2)
                {
                    actividadesVertice(listaVertices);
                }
                else if (opcionAct == 0)
                    break;
            }
        }

        else if (opcion == 0)
            break;
    }

    return 0;
}

void getListaVertices(list<Vertice> listaVertices)
{
    cout << endl;
    for (auto vertice : listaVertices)
    {
        cout << "\n"
             << endl;
        cout << vertice.nombre << endl;
        cout << "Sus arcos: " << endl;
        for (auto arco : vertice.arcos)
        {
            cout << arco.destino->nombre << endl;
        }
    }
}

void getListaActividades(list<string> listaActividades)
{
    cout << endl;
    for (auto actividad : listaActividades)
    {
        cout << actividad << endl;
    }
}

Vertice getVertice(const string &nombre, list<Vertice> listaVertices)
{
    for (auto vertice : listaVertices)
    {
        if (vertice.nombre == nombre)
        {
            return vertice;
        }
    }
    cout << "No se encontro el vertice" << endl;
}

Arco getArco(Vertice &vertice, const string &nombreDestino)
{
    for (Arco &arco : vertice.arcos)
    {
        if (arco.destino->nombre == nombreDestino)
        {
            return arco;
        }
    }
    cout << "\nNo se encontró la ruta";
}

// Obtener la actividad de un vertice
void getActividad(const std::list<std::string> &listaActividades)
{
    std::cout << "Actividades:" << std::endl;
    for (const auto &actividad : listaActividades)
    {
        std::cout << actividad << std::endl;
    }
}

void actividadesVertice(const std::list<Vertice> &vertices)
{
    for (const auto &vert : vertices)
    {
        std::cout << vert.nombre << std::endl;
        for (const auto &actPtr : vert.actividades)
        {
            std::cout << "-" << *actPtr << std::endl; // Imprime el contenido apuntado por el puntero
        }
    }
}

// Función para agregar un vértice a una lista de vértices
void createVertice(list<Vertice *> &vertices, string nombreV)
{
    Vertice nuevoVertice(nombreV);
    vertices.push_back(&nuevoVertice);
}

// Funcion para modificar vertices
void modificarVertice(Vertice *vertice, string &nuevoNombre)
{
    vertice->nombre = nuevoNombre;
}

// Función para eliminar un vértice de una lista de vértices
void deleteVertice(list<Vertice *> &vertices, const Vertice &vertice)
{
    // vertices.remove(vertice);
    cout << "Eliminaria el vertice " << vertice.nombre << endl;
}

// Función para modificar un arco
void modificarArco(Vertice &vertice, string nombreDestino, int nuevaDistancia, Vertice &nuevoDestino)
{
    Arco arco = getArco(vertice, nombreDestino);
    if (arco.distancia != 0 || !arco.destino->nombre.empty())
    {
        arco.distancia = nuevaDistancia;
        arco.destino = &nuevoDestino;
        cout << "Ruta modificada con éxito." << endl;
    }
    else
    {
        cout << "Ruta no encontrada." << endl;
    }
}

// Función para eliminar un arco
void eliminarVertice(std::list<Vertice> &listaVertices, const Vertice &vertice)
{
    auto it = std::find(listaVertices.begin(), listaVertices.end(), vertice);
    if (it != listaVertices.end())
    {
        listaVertices.erase(it);
    }
}

// Calcula la ruta más corta entre dos ciudades
void calcRutaCorta(string origen, string destino)
{
    Vertice *partida = nullptr;
    Vertice *final = nullptr;

    std::vector<int> listaDistancias;
    std::vector<std::vector<Vertice *>> listaTodasRutaVertices;
    std::vector<Vertice *> listaRutaVertices;

    for (Vertice &vertice : listaVertices)
    {
        if (vertice.nombre == origen)
        {
            partida = &vertice;
        }
        else if (vertice.nombre == destino)
        {
            final = &vertice;
        }
    }

    // Calcular la ruta más corta con la funcion
    encontrarRuta(partida, final, listaRutaVertices, listaTodasRutaVertices, listaDistancias, 0);

    if (listaTodasRutaVertices.empty())
    {
        cout << "No se encontró una ruta" << endl;
    }

    auto it = std::min_element(listaDistancias.begin(), listaDistancias.end());
    // int indice = std::distance(listaDistancias.begin(), it);

    if (it != listaDistancias.end())
    {
        int indice = std::distance(listaDistancias.begin(), it);
        cout << "La ruta más corta es: " << endl;
        // cout << listaRutaVertices[indice]->nombre <<  " Uy" << endl;
        for (size_t i = 0; i < listaTodasRutaVertices[indice].size(); i++)
        {
            cout << listaTodasRutaVertices[indice][i]->nombre;
            if (i < listaTodasRutaVertices[indice].size() - 1)
            {
                cout << " - ";
            }
        }
        cout << "La distancia es: " << listaDistancias[indice] << endl;
    }
    else
    {
        cout << "No se encontró una ruta (Llego al final)" << endl;
    }
}

void encontrarRuta(Vertice *origen, Vertice *destino, std::vector<Vertice *> &listaRutaVertices, std::vector<std::vector<Vertice *>> &listaRutaTodosVertices, std::vector<int> &listaDistancias, int distanciaTotal)
{
    if (origen->visitado)
        return;

    origen->visitado = true;
    listaVertices.push_back(*origen);

    if (origen->nombre == destino->nombre)
    {
        listaRutaTodosVertices.push_back(listaRutaVertices);
        listaDistancias.push_back(distanciaTotal);
        // cout << "Ruta encontrada (con distancia de " << distanciaTotal << ") - Pasando por: " << origen->nombre << "." << endl;

        return;
    }

    for (Arco &arco : origen->arcos)
    {
        if (arco.destino->nombre != origen->nombre)
        {
            // cout << "Pasando por: " << origen->nombre << " - " << arco.destino->nombre << endl;
            encontrarRuta(arco.destino, destino, listaRutaVertices, listaRutaTodosVertices, listaDistancias, distanciaTotal + arco.distancia);
        }
    }
    origen->visitado = false;
    listaRutaVertices.pop_back();
}

void agregarPersona()
{
    char genero;
    int edad;
    char origen[15], destino[15], actividad[30];
    cout << "Ingrese el genero de la persona(F/M): ";
    cin >> genero;
    cin.ignore();
    cout << "Ingrese la edad de la persona: ";
    cin >> edad;
    cin.ignore();
    cout << "Ingrese el origen de la persona: ";
    cin.getline(origen, 15);
    cout << "Ingrese el destino de la persona: ";
    cin.getline(destino, 15);
    cout << "Ingrese la actividad de la persona: ";
    cin.getline(actividad, 30);

    Persona nuevaPersona(genero, edad, origen, destino, actividad);
    fstream file("persons.bin", ios::in | ios::binary | ios::app);

    file.write(reinterpret_cast<char *>(&nuevaPersona), sizeof(Persona));
    file.close();
    cout << "Persona agregada con éxito!" << endl;
}

// Amplitud
void amplitud(Vertice *inicio)
{
    std::queue<Vertice *> cola;
    std::list<Vertice *> visitados;

    cola.push(inicio);
    visitados.push_back(inicio);

    while (!cola.empty())
    {
        Vertice *actual = cola.front();
        cola.pop();

        std::cout << actual->nombre << " ";

        for (const Arco &arco : actual->arcos)
        {
            Vertice *vecino = arco.destino;
            if (!vecino->visitado)
            {
                cola.push(vecino);
                visitados.push_back(vecino);
                vecino->visitado = true;
            }
        }
    }
}

// Profundidad
void profundidad(Vertice *inicio)
{
    if (!inicio)
        return;

    std::list<Vertice *> visitados;
    profundidadRecursivo(inicio, visitados);
}

void profundidadRecursivo(Vertice *actual, std::list<Vertice *> &visitados)
{
    if (!actual)
        return;

    std::cout << actual->nombre << " ";
    visitados.push_back(actual);
    actual->visitado = true;

    for (const Arco &arco : actual->arcos)
    {
        Vertice *vecino = arco.destino;
        if (!vecino->visitado)
        {
            profundidadRecursivo(vecino, visitados);
        }
    }
}