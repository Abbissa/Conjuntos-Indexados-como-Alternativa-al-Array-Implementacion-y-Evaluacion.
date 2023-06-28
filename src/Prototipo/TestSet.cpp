#include <iostream>
#include <sys/time.h>
#include <set>
#include <algorithm>
#include "../InsercionEnListas/puntuationSmall.hpp"
#include "../InsercionEnListas/puntuationMedium.hpp"
#include "../InsercionEnListas/puntuationLarge.hpp"

#if (testType == 0)
typedef puntuationSmall puntuation;
#define TYPE "Small"
#elif (testType == 1)
typedef puntuationMedium puntuation;
#define TYPE "Medium"
#elif (testType == 2)
typedef puntuationLarge puntuation;
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
    set<puntuation> set;
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    double time;
    int memory;
    // int j = 0;
    for (size_t i = 0; i < size; i++)
    {

        cin >> time;
        cin >> memory;
        puntuation p = puntuation(time, memory);
        set.insert(p);
        // j++;
    }
    // cerr << j << endl;
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;

    cout << "TestSet,INSERT," << TYPE << "," << set.size() << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);
    // j = 0;
    while (cin >> time && !cin.eof())
    {
        // j++;
        cin >> memory;
        puntuation p = puntuation(time, memory);
        set.erase(set.begin());
        set.insert(p);
    }
    // cerr << j << endl;
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "TestSet,USAGE," << TYPE << "," << set.size() << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);
    int tam = set.size();
    puntuation p = *set.begin();
    set.erase(set.begin());
    while (set.size() > 0)
    {
        puntuation temp = *set.begin();
        set.erase(set.begin());
        if (p > temp)
        {
            cerr << "Error: Set no ordenado" << endl;
            return 1;
        }
        if (p == temp)
            cerr << "test" << endl;
        p = temp;
    }
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "TestSet,REMOVE," << TYPE << "," << tam << "," << tiempo << endl;

    return 0;
}
