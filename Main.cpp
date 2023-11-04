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


struct Persona {
    char genero;
    int edad;
    char origen[15] ;
    char  destino[15];
    char  actividad[30];

    Persona( char genero, int edad, const char* origen,const char *destino, char* actividad);
};

Persona::Persona(char genero, int edad, const char *origen1, const char *destino1, char *actividad1) :
    genero(genero), edad(edad) {

    strcpy(origen, origen1);
    strcpy(destino, destino1);
    strcpy(actividad, actividad1);
    }


struct Nodo {
    list<Persona> lista;
    Nodo* left;
    Nodo* right;

    Nodo(list<Persona> lista){
        this->lista = lista;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// Prototypes
list<Vertice> listaVertices;
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

void getListaVertices(list<Vertice> listaVertices);
Vertice getVertice(const string &nombre, list<Vertice > listaVertices);

void dijkstra(Vertice *inicio, Vertice *destino);

void cargarDatos(){
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

    fstream file("persons.bin", ios::in | ios::out |ios::binary |ios::trunc );

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

void leerArchivo(){
 // Read from the binary file
   // ifstream file2("persons.bin", ios::binary);
    fstream file2("persons.bin", ios::in | ios::out |ios::binary );
//
    Persona p = Persona('z', 0, "", "", "");
    file2.read(reinterpret_cast<char *>(&p), sizeof(Persona));

    while (!file2.eof()) {
        cout << "\n" << endl;
        if(p.genero == 'M')
            cout << "hombre de ";
        else
            cout << "mujer de";

        cout << " " << p.edad;
        cout << " años está en " << p.origen;
        cout <<  " y quiere viajar a " << p.destino;
        cout << " para " << p.actividad;
        file2.read(reinterpret_cast<char *>(&p), sizeof(p));
    }
}


//Verificar si el numero ya existe en el array
bool insideArray(list<int> array, int num){
    for (int i = 0; i < array.size(); i++)
    {
        if(array.front() == num){
            cout << "El numero ya existe" << endl;
            return true;    
        }
        array.pop_front();
    }
    return false;
}


// Crear el arbol binario en base a la lista de personas y el orden que el usuario escoga
void createTree(list<Persona> listaPersonas) {
    // Crear el nodo raíz con la lista de personas
    Nodo *root = new Nodo(listaPersonas);

    //Solictar el orden al usuario
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
    //Print order 
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

    for(int i = 0; i < 4; i++){
        if(orden.front() == 1){
            //Ordenar por genero
            list<Persona> listaHombres;
            list<Persona> listaMujeres;
            list<Persona> listaTmp = root->lista;
            while (!listaTmp.empty())
            {
                if(listaTmp.front().genero == 'M')
                    listaHombres.push_back(listaTmp.front());
                else
                    listaMujeres.push_back(listaTmp.front());
                listaTmp.pop_front();
            }
            //Crear nodos hijos
            Nodo *hijo1 = new Nodo(listaHombres);
            Nodo *hijo2 = new Nodo(listaMujeres);
            root->left = hijo1;
            root->right = hijo2;
        } 
        else if(orden.front() == 2){
            //Ordenar por edad
            list<Persona> lista18_30;
            list<Persona> lista31_64;
            list<Persona> lista65;

            list<Persona> listaTmp = root->lista;
            while (!listaTmp.empty())
            {
                if(listaTmp.front().edad >= 18 && listaTmp.front().edad <= 30)
                    lista18_30.push_back(listaTmp.front());
                else if(listaTmp.front().edad >= 31 && listaTmp.front().edad <= 64)
                    lista31_64.push_back(listaTmp.front());
                else
                    lista65.push_back(listaTmp.front());
                listaTmp.pop_front();
            }

            //Crear nodos hijos
            Nodo *hijo1 = new Nodo(lista18_30);
            Nodo *hijo2 = new Nodo(lista31_64);
            Nodo *hijo3 = new Nodo(lista65);
            root->left = hijo1;
            root->right = hijo2;
            hijo2->right = hijo3;
        }
        else if(orden.front() == 3){

        }
        else if(orden.front() == 4){

        }
    }

    //Mostrar el arbol por niveles
    cout << "\n\nMostrando el arbol por niveles: " << endl;
    queue<Nodo*> cola;
    cola.push(root);
    while (!cola.empty())
    {
        Nodo *tmp = cola.front();
        cola.pop();
        cout << "\nNodo: " << endl;
        list<Persona> listaTmp = tmp->lista;
        while (!listaTmp.empty())
        {
            cout << listaTmp.front().genero << " " << listaTmp.front().edad << " " << listaTmp.front().origen << " " << listaTmp.front().destino << " " << listaTmp.front().actividad << endl;
            listaTmp.pop_front();
        }
        if(tmp->left != nullptr)
            cola.push(tmp->left);
        if(tmp->right != nullptr)
            cola.push(tmp->right);
    }
}

//Crear arreglo con los datos de las personas para el arbol
void displayTree(){
    fstream file2("persons.bin", ios::in | ios::out |ios::binary );
    Persona p = Persona('z', 0, "", "", "");
    file2.read(reinterpret_cast<char *>(&p), sizeof(Persona));
    //Lista de personas
    list<Persona> listaPersonas;

    while (!file2.eof()) {
        listaPersonas.push_back(p);
        file2.read(reinterpret_cast<char *>(&p), sizeof(p));
    }

    createTree(listaPersonas);
}

// Menu
void menu(){
    cout<<"\n1. Leer archivo";
    cout<<"\n2. Ruta corta";
    cout<<"\n3. Mostrar vertices";
    cout << "\n4. Consultar Personas";
    cout<<"\n0. Salir \n";
}

int main()
{
    string origen, destino;


    //list<string> actividades = {"Shopping", "Ir al parque", "Ir al Mall", "Termales", "Senderismo", "Canopy", "Observación de aves", "Serpentario", "Ir al Rio", "Ir al Museo", "Ir al Teatro", "Ir a la playa", "Tour dela_piña", "Campo_de_girasoles", "Ir_al_mirador", "Ir_a_la_catarata", "Ir_al_centro_civico", "Ir_al_parque", "Comprar_arboles_de_navidad", "Ver_vacas", "Ir_a_la_gasolinera"};

    cargarDatos(); //Carga de datos

    int opcion;
    while(true){
        menu();
        cin>>opcion;

        if(opcion == 1){
            leerArchivo();
            cout<<"\n \nArchivo leido \n \n";
        }
        else if(opcion==0)
            break;
        else if(opcion == 3)
              // Show lista
                getListaVertices(listaVertices);
        else if(opcion == 2){

                    //string ciudad1, ciudad2;
                    cout << "Ingrese el nombre de la ciudad de partida: ";
                    cin >> origen;
                    cin.ignore();

                    cout << "Ingrese el nombre de la ciudad de destino: ";
                    cin >> destino;
                    cin.ignore();


                // Show ciudades selected
                cout << "Ciudad de partida: " << origen << endl;
                cout << "Ciudad de destino: " << destino << endl;

                Vertice origenVertice = getVertice(origen, listaVertices);
                Vertice destinoVertice = getVertice(destino, listaVertices);

                cout << "Ciudad de partida: " << origenVertice.nombre << endl;
                cout << "Ciudad de destino: " << destinoVertice.nombre << endl;

                int dist = calcDistancia(&origenVertice, &destinoVertice, " ", 0);
                cout << "\nLa ruta es: " << origen + "-" + destino << ". La distancia es: " << dist;

//                string actividadEscogida = getActividad("Ir a la playa", destinoVertice);
//                cout << "\nLa actividad escogida es: " << actividadEscogida << endl;



        }
        else if (opcion == 4)
        {
            cout << "Desplegando valores con el arbol binario: \n \n";
            displayTree();
        }

    }
    return 0;
}

// Funcion para calcular la distancia mas corta (Retorna la distancia mas corta entre dos ciudades como un entero)
int distanciaMenor = 0;
string rutaMenor = "";
int calcDistancia(Vertice *origen, Vertice *destino, string ruta, int dis)
{
    cout << "\nOrigen: " << origen->nombre << " Destino: " << destino->nombre << " Ruta: " << ruta << " Distancia: " << dis;
    if ((origen == NULL) or (origen->visitado == true))
        return 0;

    if (origen->nombre == destino->nombre)
    {
        cout << "\nLa ruta es: " << ruta + "-" + destino->nombre << " La distancia es: " << dis;
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
        cout << "\nLa ruta es: " << ruta + "-" + destino->nombre << " La distancia es: " << dis << " - Dentro del while" << endl;
        calcDistancia(tempA->destino, destino, ruta + origen->nombre, dis + tempA->distancia);
        cout << "Salió" << endl;
        tempA++;
    }
    origen->visitado = false;
    return distanciaMenor;
}

// Funcion para obtener los vertices de una lista
void getListaVertices(list<Vertice> listaVertices)
{
    cout << endl;
    for (auto vertice : listaVertices)
    {
       // cout << vertice << endl;
        cout << vertice.nombre << endl;
    }
}

// Funcion para obtener un vertice especifico en base al nombre dentro de una lista
Vertice getVertice(const string &nombre, list<Vertice> listaVertices)
{
    for (auto vertice : listaVertices)
    {
        if (vertice.nombre == nombre)
        {
//            cout << vertice << endl;
            return vertice;
        }
    }
    cout << "No se encontro el vertice" << endl;
//    return vertice;
}


// Obtener la actividad de un vertice
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