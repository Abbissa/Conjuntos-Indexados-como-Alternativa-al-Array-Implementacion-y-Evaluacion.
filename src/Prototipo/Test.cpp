#include <random>
#include <iostream>
#include <sys/time.h>

#include "HollowList.hpp"
#include "ptrHollowList.hpp"
#include "../InsercionEnListas/puntuacionSmall.hpp"
#include "../InsercionEnListas/puntuacionMedium.hpp"
#include "../InsercionEnListas/puntuacionLarge.hpp"

template <typename T>
#if (GLType == 0)
using HL = HollowList<T>;
#define NOMBRE "HollowList"
#elif (GLType == 1)
using HL = HollowList<T>;
#define NOMBRE "ptrHollowList"
#endif

#if (testType == 0)
typedef puntuacionSmall puntuacion;
#elif (testType == 1)
typedef puntuacionMedium puntuacion;
#elif (testType == 2)
typedef puntuacionLarge puntuacion;

#endif

using namespace std;
int runTestCase(int, int);

int main(int argc, char const *argv[])
{
    int size = 100000;
    int THRESHOLD = 256;
    if (argc >= 2)

        size = atoi(argv[1]);
    if (argc >= 3)
        THRESHOLD = atoi(argv[2]);

    runTestCase(size, THRESHOLD);
}

int runTestCase(int elems, int THRESHOLD)
{
    HL<puntuacion> hl;
    hl.THRESHOLD = THRESHOLD;
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    int size_max = 0;
    int memory;
    double time;
    for (size_t i = 0; i < elems; i++)
    {

        cin >> time;
        cin >> memory;
        puntuacion p = puntuacion(time, memory);
        hl.insert(p);
        size_max++;
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    gettimeofday(&ti, nullptr);

    while (cin >> time && !cin.eof())
    {
        cin >> memory;
        puntuacion p = puntuacion(time, memory);
        hl.remove();
        hl.insert(p);
    }
    gettimeofday(&tf, nullptr);

    cout << NOMBRE << ","
         << "FAST,INSERT," << size_max << "," << tiempo << endl;
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << NOMBRE << ","
         << "FAST,USAGE," << size_max << "," << tiempo << endl;

    puntuacion p = hl.remove();
    int errores = 0;
    for (size_t i = 0; i < size_max - 1; i++)
    {

        puntuacion temp = hl.remove();
        if (temp > p)
        {
            errores++;
            cerr << i << endl;
        }
        p = temp;
    }
    if (errores > 0)
    {
        cerr << "Error: HollowList no ordenado" << endl;
        cerr << "Error: " << errores << endl;
        return 1;
    }
    return 0;
}
