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
#define TYPE "Small"
#elif (testType == 1)
typedef puntuacionMedium puntuacion;
#define TYPE "Medium"
#elif (testType == 2)
typedef puntuacionLarge puntuacion;
#define TYPE "Large"

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

    double time;
    int memory;
    for (size_t i = 0; i < size; i++)
    {

        cin >> time;
        cin >> memory;
        puntuacion p = puntuacion(time, memory);
        bh.insert(p);
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;

    cout << "TestBinaryHeap,INSERT," << TYPE << "," << bh.size() << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);

    while (cin >> time && !cin.eof())
    {
        cin >> memory;
        puntuacion p = puntuacion(time, memory);
        bh.extractMin();
        bh.insert(p);
    }
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "TestBinaryHeap,USAGE," << TYPE << "," << bh.size() << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);
    int tam = bh.size();
    puntuacion p = bh.extractMin();
    while (bh.empty() == false)
    {
        puntuacion temp = bh.extractMin();
        if (temp < p)
        {
            cerr << "ERROR" << endl;
            return 1;
        }
        p = temp;
    }
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "TestBinaryHeap,REMOVE," << TYPE << "," << tam << "," << tiempo << endl;
    return 0;
}
