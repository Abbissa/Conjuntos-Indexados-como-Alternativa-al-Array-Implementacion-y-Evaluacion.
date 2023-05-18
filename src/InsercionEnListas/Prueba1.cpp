#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <chrono>
#include <iomanip>

#include "puntuacionSmall.hpp"
#include "puntuacionMedium.hpp"
#include "puntuacionLarge.hpp"
typedef puntuacionSmall puntuacion;
using namespace std;

void prueba1();
void prueba2();
void prueba3();

int main()
{
    puntuacion p = puntuacion(1, 2);
    puntuacionMedium p2 = puntuacionMedium(1, 2);
    puntuacionLarge p3 = puntuacionLarge(1, 2);
    cout << sizeof(p) << endl;
    cout << sizeof(p2) << endl;
    cout << sizeof(p3) << endl;

    // prueba1();
    // prueba2();
    // prueba3();
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
    size_t i = 0;
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

    size_t i = 0;
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
    int n = 100000;
    int size = n;
    srand(time(NULL));
    auto start = std::chrono::system_clock::now();
    while (n--)
    {
        ti = (double)(rand());
        memory = rand();

        puntuacion p = puntuacion(ti, memory);
        auto it = upper_bound(datos.begin(), datos.end(), p);
        datos.insert(it, p);
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to fill and iterate a vector of size " << size << std::setw(9) << " Integer : " << diff.count() << " s\n";
}