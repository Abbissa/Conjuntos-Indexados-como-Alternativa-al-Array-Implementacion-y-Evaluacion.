#include <iostream>
#include <sys/time.h>
#include <vector>
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
    vector<int> vec;
    for (size_t i = 0; i < size; i++)
    {
        cin >> num;
        auto it = upper_bound(vec.begin(), vec.end(), num);
        vec.insert(it, num);
        size_max++;
    }

    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;

    num = vec[0];
    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[i] < num)
        {
            cerr << "Error: Vector no ordenado" << endl;
            return 1;
        }
        num = vec[i];
    }

    cout << "Vector,SLOW,INSERT," << size_max << "," << tiempo << endl;
    gettimeofday(&ti, nullptr);

    while (cin >> num && !cin.eof())
    {
        vec.erase(vec.begin());
        auto it = upper_bound(vec.begin(), vec.end(), num);
        vec.insert(it, num);
    }
    gettimeofday(&tf, nullptr);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    cout << "Vector,SLOW,USAGE," << size_max << "," << tiempo << endl;

    return 0;
}
