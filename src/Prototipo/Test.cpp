#include <random>
#include <iostream>
#include <sys/time.h>

#include "HollowList.hpp"
#include "ptrHollowList.hpp"

#if (GLType == 0)
HollowList<int> HL;
#define NOMBRE "HollowList"
#elif (GLType == 1)
ptrHollowList<int> HL;
#define NOMBRE "ptrHollowList"
#endif

using namespace std;
int main()
{
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    int size_max = 0;
    int num;
    while (cin >> num && !cin.eof())
    {
        HL.insert(num);
        size_max++;
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
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
    cout << NOMBRE << "," << size_max << "," << tiempo << endl;

    return 0;
}
