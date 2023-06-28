#include <random>
#include <iostream>
#include <sys/time.h>
#include <climits>

int generateRandomNumbers(int);
int generateInversedOrderedNumbers(int);
int generateOrderedNumbers(int);

#if (GNType == 0)
#define GEN_NUMBERS generateRandomNumbers
#define GEN "Random"
#elif (GNType == 1)
#define GEN_NUMBERS generateOrderedNumbers
#define GEN "Ordered"
#elif (GNType == 2)
#define GEN_NUMBERS generateInversedOrderedNumbers
#define GEN "Inversed"
#endif

std::mt19937 gen(time(nullptr));
size_t size_max = 10000;
int min_value = 0;
std::uniform_int_distribution<int> dis;

int main(int argc, char *argv[])
{

    if (argc == 2)
    {
        size_max = strtol(argv[1], nullptr, 10);
    }
    else if (argc == 3)
    {
        min_value = strtol(argv[1], nullptr, 10);
        size_max = strtol(argv[2], nullptr, 10);
    }
    dis = std::uniform_int_distribution<int>(min_value, 2 * size_max);

    for (size_t i = 0; i < size_max; i++)
    {
        printf("%d ", GEN_NUMBERS(i));
    }

    return 0;
}

int generateRandomNumbers(int)
{

    return dis(gen);
}

int generateInversedOrderedNumbers(int num)
{
    return size_max - num;
}

int generateOrderedNumbers(int num)
{
    return num + min_value;
}