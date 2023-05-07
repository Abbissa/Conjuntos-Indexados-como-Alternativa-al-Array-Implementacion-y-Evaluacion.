#include <iostream>
#include <sys/time.h>
#include <set>
#include <algorithm>
#include "../InsercionEnListas/puntuacionSmall.hpp"
#include "../InsercionEnListas/puntuacionMedium.hpp"
#include "../InsercionEnListas/puntuacionLarge.hpp"

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
    set<puntuacion> set;
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
        set.insert(p);
        size_max++;
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;

    cout << "Set,FAST,INSERT," << size_max << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);

    while (cin >> time && !cin.eof())
    {
        cin >> memory;
        puntuacion p = puntuacion(time, memory);
        set.erase(set.begin());
        set.insert(p);
    }
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "Set,FAST,USAGE," << size_max << "," << tiempo << endl;

    puntuacion p = *set.begin();
    set.erase(set.begin());
    while (set.size() > 0)
    {
        puntuacion temp = *set.begin();
        set.erase(set.begin());
        if (p > temp)
        {
            cerr << "Error: Set no ordenado" << endl;
            return 1;
        }
        p = temp;
    }

    return 0;
}
