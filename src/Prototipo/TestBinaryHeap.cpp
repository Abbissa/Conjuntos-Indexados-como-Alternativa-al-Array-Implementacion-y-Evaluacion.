#include <iostream>
#include <sys/time.h>
#include <set>
#include <algorithm>
#include "../InsercionEnListas/puntuacionSmall.hpp"
#include "../InsercionEnListas/puntuacionMedium.hpp"
#include "../InsercionEnListas/puntuacionLarge.hpp"
#include "./BinaryHeapArray.hpp"

#if (testType == 0)
typedef puntuacionSmall puntuacion;
#elif (testType == 1)
typedef puntuacionMedium puntuacion;
#elif (testType == 2)
typedef puntuacionLarge puntuacion;

#endif

using namespace std;
int runTestCase(int);

int main(int argc, char const *argv[])
{
    int size = 100000;
    if (argc >= 2)

        size = atoi(argv[1]);

    runTestCase(size);
}

int runTestCase(int size)
{
    BinaryHeap<puntuacion> bh;
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    int size_max = 0;
    double time;
    int memory;
    for (size_t i = 0; i < size; i++)
    {

        cin >> time;
        cin >> memory;
        puntuacion p = puntuacion(time, memory);
        bh.insert(p);
        size_max++;
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;

    cout << "BinaryHeap,FAST,INSERT," << size_max << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);

    while (cin >> time && !cin.eof())
    {
        cin >> memory;
        puntuacion p = puntuacion(time, memory);
        bh.delete_min();
        bh.insert(p);
    }
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "BinaryHeap,FAST,USAGE," << size_max << "," << tiempo << endl;

    puntuacion p = bh.delete_min();
    while (bh.is_empty() == false)
    {
        puntuacion temp = bh.delete_min();
        if (temp < p)
        {
            cerr << "ERROR" << endl;
            return 1;
        }
        p = temp;
    }
    return 0;
}
