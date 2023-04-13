#include <random>
#include <iostream>
#include <sys/time.h>

#include "HollowList.hpp"
#include "ptrHollowList.hpp"

#if (GLType == 0)
HollowList<int> HL;
#define NOMBRE "HollowList"
#define TYPE "SLOW"
#elif (GLType == 1)
ptrHollowList<int> HL;
#define NOMBRE "ptrHollowList"
#define TYPE "FAST"
#endif

using namespace std;
int main(int argc, char const *argv[])
{
    int elems = 10000;
    if (argc == 2)
    {
        elems = atoi(argv[1]);
    }

    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    int size_max = 0;
    int num;
    for (size_t i = 0; i < elems; i++)
    {
        cin >> num;
        HL.insert(num);
        size_max++;
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    gettimeofday(&ti, nullptr);

    while (cin >> num && !cin.eof())
    {
        HL.remove();
        HL.insert(num);
    }
    gettimeofday(&tf, nullptr);

    num = HL.remove();
    for (size_t i = 0; i < size_max - 1; i++)
    {

        int temp = HL.remove();
        if (temp > num)
        {
            cerr << "Error: HollowList no ordenado" << endl;
            return 1;
        }
        num = temp;
    }

    cout << NOMBRE << "," << TYPE << ",INSERT," << size_max << "," << tiempo << endl;
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << NOMBRE << "," << TYPE << ",USAGE," << size_max << "," << tiempo << endl;

    return 0;
}
