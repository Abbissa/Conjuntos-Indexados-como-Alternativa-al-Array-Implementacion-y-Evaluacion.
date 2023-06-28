#include <iostream>
#include <sys/time.h>
#include <set>
#include <algorithm>

#include "BinaryHeapArray.hpp"
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
    BinaryHeap<puntuation> bh;
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    double time;
    int memory;
    for (size_t i = 0; i < size; i++)
    {

        cin >> time;
        cin >> memory;
        puntuation p = puntuation(time, memory);
        bh.insert(p);
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;

    cout << "TestBinaryHeap,INSERT," << TYPE << "," << bh.size() << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);

    while (cin >> time && !cin.eof())
    {
        cin >> memory;
        puntuation p = puntuation(time, memory);
        bh.extractMin();
        bh.insert(p);
    }
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "TestBinaryHeap,USAGE," << TYPE << "," << bh.size() << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);
    int tam = bh.size();
    puntuation p = bh.extractMin();
    while (bh.empty() == false)
    {
        puntuation temp = bh.extractMin();
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
