#include <random>
#include <iostream>
#include "GappedList.hpp"
#include "GappedListV2.hpp"

int generateRandomNumbers(int);
int generateInversedOrderedNumbers(int);
int generateOrderedNumbers(int);
#if (GNType == 0)
#define GEN_NUMBERS(n) generateRandomNumbers(n)
#elif (GNType == 1)
#define GEN_NUMBERS(n) generateInversedOrderedNumbers(n)
#elif (GNType == 2)
#define GEN_NUMBERS(n) generateOrderedNumbers(n)
#endif

#if (GLType == 0)
GappedList<int> GL;
#elif (GLType == 1)
GappedListV2<int> GL;
#endif

size_t size_max = 10000;
int min_value = 0;

using namespace std;
int main(int argc, char *argv[])
{

    if (argc == 2)
    {
        size_max = strtol(argv[1], nullptr, 10);
    }
    else if (argc == 3)
    {
        size_max = strtol(argv[1], nullptr, 10);
        min_value = strtol(argv[2], nullptr, 10);
    }

    for (size_t i = 0; i < size_max; i++)
    {
        int num = GEN_NUMBERS(i);

        GL.insert(num);
    }
    int num = GL.remove();
    for (size_t i = 0; i < size_max - 1; i++)
    {

        int temp = GL.remove();
        if (temp > num)
            return 1;
        num = temp;
    }

    return 0;
}

int generateRandomNumbers(size_t)
{
    mt19937 gen(time(nullptr));
    uniform_int_distribution<int> dis(min_value, size_max);
    return dis(gen);
}

int generateInversedOrderedNumbers(size_t num)
{
    return size_max - num;
}

int generateOrderedNumbers(size_t num)
{
    return num;
}
