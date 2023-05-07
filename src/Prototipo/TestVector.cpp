#include <iostream>
#include <sys/time.h>
#include <vector>
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
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    int size_max = 0;
    double time;
    int memory;
    vector<puntuacion> vec;

    for (size_t i = 0; i < size; i++)
    {
        cin >> time;
        cin >> memory;
        puntuacion p = puntuacion(time, memory);
        auto it = upper_bound(vec.begin(), vec.end(), p);
        vec.insert(it, p);
        size_max++;
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    gettimeofday(&ti, nullptr);

    puntuacion p = vec[0];
    while (cin >> time && !cin.eof())
    {
        cin >> memory;
        p = puntuacion(time, memory);
        vec.erase(vec.begin());
        auto it = upper_bound(vec.begin(), vec.end(), p);
        vec.insert(it, p);
    }
    gettimeofday(&tf, nullptr);
    cout << "Vector,SLOW,INSERT," << size_max << "," << tiempo << endl;
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "Vector,SLOW,USAGE," << size_max << "," << tiempo << endl;
    p = vec[0];
    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[i] < p)
        {
            cerr << "Error: Vector no ordenado" << endl;
            return 1;
        }
        p = vec[i];
    }

    return 0;
}
