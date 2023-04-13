#include <iostream>
#include <sys/time.h>
#include <set>
#include <algorithm>

using namespace std;
int main(int argc, char const *argv[])
{
    int size = 10000;
    if (argc == 2)
    {
        size = atoi(argv[1]);
    }
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, nullptr);

    int size_max = 0;
    int num;
    set<int> set;
    for (size_t i = 0; i < size; i++)
    {
        cin >> num;
        set.insert(num);
        size_max++;
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;

    cout << "Set,FAST,INSERT," << size_max << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);

    while (cin >> num && !cin.eof())
    {
        set.erase(set.begin());
        set.insert(num);
    }
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "Set,FAST,USAGE," << size_max << "," << tiempo << endl;

    return 0;
}
