#include <random>
#include <iostream>
#include <sys/time.h>

#include "HollowList.hpp"
#include "ptrHollowList.hpp"
#include "HollowListv2.hpp"

#include "../InsercionEnListas/puntuationSmall.hpp"
#include "../InsercionEnListas/puntuationMedium.hpp"
#include "../InsercionEnListas/puntuationLarge.hpp"
template <typename T>
#if (HLType == 0)
using HL = HollowList<T>;
#define NOMBRE "HollowList"
#elif (HLType == 1)
using HL = ptrHollowList<T>;
#define NOMBRE "ptrHollowList"
#elif (HLType == 2)
using HL = HollowListv2<T>;
#define NOMBRE "HollowListv2"
#endif

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
int runTestCase(int, int);

int main(int argc, char const *argv[])
{
    int size = 100000;
    int threshold = 256;
    if (argc >= 2)

        size = atoi(argv[1]);
    if (argc >= 3)
        threshold = atoi(argv[2]);

    return runTestCase(size, threshold);
}

int runTestCase(int elems, int threshold)
{
    HL<puntuation> hl;
    hl.threshold = threshold;
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    int memory;
    double time;
    for (size_t i = 0; i < elems; i++)
    {

        cin >> time;
        cin >> memory;
        puntuation p = puntuation(time, memory);
        hl.insert(p);
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    gettimeofday(&ti, nullptr);

    while (cin >> time && !cin.eof())
    {
        cin >> memory;
        puntuation p = puntuation(time, memory);
        hl.remove();
        hl.insert(p);
    }
    gettimeofday(&tf, nullptr);

    cout << NOMBRE << "-" << hl.threshold << ","
         << "INSERT," << TYPE << "," << hl.size() << "," << tiempo << endl;
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << NOMBRE << "-" << hl.threshold << ","
         << "USAGE," << TYPE << "," << hl.size() << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);
    int tam = hl.size();
    puntuation p = hl.remove();
    while (!hl.isEmpty())
    {

        puntuation temp = hl.remove();
        if (temp > p)
        {
            cerr << "Error: HollowList no ordenado" << endl;
            return 1;
        }
        p = temp;
    }
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << NOMBRE << "-" << hl.threshold << ","
         << "REMOVE," << TYPE << "," << tam << "," << tiempo << endl;
    return 0;
}
