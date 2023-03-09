#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <chrono>
#include <iomanip>

#include "puntuacion.h"

using namespace std;
void prueba1();
void prueba2();
void prueba3();

int main()
{
    // prueba1();
    // prueba2();
    prueba3();
}

void prueba1()
{
    ifstream fich("input.txt");

    if (!fich.is_open())
    {
        cout << "Error al abrir ejemplo.dat\n";
        exit(EXIT_FAILURE);
    }
    vector<puntuacion> datos;
    double time;
    int memory;
    while (fich >> time)
    {
        fich >> memory;
        puntuacion p = puntuacion(time, memory);
        datos.push_back(p);
    }
    int i = 0;
    while (i < datos.size())
    {
        cout << datos.at(i);
        i++;
    }
}

void prueba2()
{
    ifstream fich("input.txt");

    if (!fich.is_open())
    {
        cout << "Error al abrir ejemplo.dat\n";
        exit(EXIT_FAILURE);
    }
    vector<puntuacion> datos;
    double time;
    int memory;
    while (fich >> time)
    {
        fich >> memory;
        puntuacion p = puntuacion(time, memory);
        auto it = lower_bound(datos.begin(), datos.end(), p);
        datos.insert(it, p);
    }
    int i = 0;
    while (i < datos.size())
    {
        cout << datos.at(i);
        i++;
    }
}
void prueba3()
{
    vector<puntuacion> datos;
    double ti;
    int memory;
    int n = 10000;
    int size = n;
    srand(time(NULL));
    auto start = std::chrono::system_clock::now();
    while (n--)
    {

        ti = (double)(rand());
        memory = rand();

        puntuacion p = puntuacion(ti, memory);
        auto it = lower_bound(datos.begin(), datos.end(), p);
        datos.insert(it, p);
    }
    int i = 0;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to fill and iterate a vector of size " << size << std::setw(9) << " ints : " << diff.count() << " s\n";
}