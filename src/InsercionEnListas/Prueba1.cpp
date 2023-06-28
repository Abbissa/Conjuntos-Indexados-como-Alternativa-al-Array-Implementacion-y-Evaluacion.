#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <chrono>
#include <iomanip>

#include "puntuationSmall.hpp"
#include "puntuationMedium.hpp"
#include "puntuationLarge.hpp"
typedef puntuationSmall puntuation;
using namespace std;

void prueba1();
void prueba2();
void prueba3();

int main()
{
    puntuation p = puntuation(1, 2);
    puntuationMedium p2 = puntuationMedium(1, 2);
    puntuationLarge p3 = puntuationLarge(1000000000, 2000000000);
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
    vector<puntuation> datos;
    double time;
    int memory;
    while (fich >> time)
    {
        fich >> memory;
        puntuation p = puntuation(time, memory);
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
    vector<puntuation> datos;
    double time;
    int memory;
    while (fich >> time)
    {
        fich >> memory;
        puntuation p = puntuation(time, memory);
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
    vector<puntuation> datos;
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

        puntuation p = puntuation(ti, memory);
        auto it = upper_bound(datos.begin(), datos.end(), p);
        datos.insert(it, p);
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to fill and iterate a vector of size " << size << std::setw(9) << " Integer : " << diff.count() << " s\n";
}