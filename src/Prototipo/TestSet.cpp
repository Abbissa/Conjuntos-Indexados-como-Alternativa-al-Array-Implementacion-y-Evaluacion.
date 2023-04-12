#include <iostream>
#include <sys/time.h>
#include <set>
#include <algorithm>

using namespace std;
int main()
{
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    int size_max = 0;
    int num;
    set<int> set;
    while (cin >> num && !cin.eof())
    {

        set.insert(num);
        size_max++;
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;

    cout << "Set," << size_max << "," << tiempo << endl;

    return 0;
}
