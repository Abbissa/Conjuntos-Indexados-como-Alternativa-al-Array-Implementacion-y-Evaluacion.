#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

typedef struct puntuacion
{
    double time;
    int memory;
} puntuacion;

void add(puntuacion, int);
int binarySearchRec(puntuacion, int, int);
int binarySearchIter(puntuacion, int, int);
int less(puntuacion, puntuacion);
int equals(puntuacion, puntuacion);

#if (BSType == 0)
#define BS(b, inf, sup) binarySearchRec(b, inf, sup)
#else
#define BS(b, inf, sup) binarySearchIter(b, inf, sup)
#endif

int listSize = 0;
int maxElems = 0;
puntuacion *list;
size_t baseMem = 128;
int main(int argc, char **argv)
{
    size_t size = 10000;
    if (argc == 2)
    {
        size = strtol(argv[1], NULL, 10);
    }
    puntuacion p;
    list = (puntuacion *)calloc(baseMem, sizeof(puntuacion));
    maxElems = baseMem;
    srand(time(NULL));

    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);

    for (size_t i = 0; i < size; i++)
    {

        p.time = (double)(rand() % 100);
        p.memory = rand() % 100;

        int in = BS(p, 0, listSize);

        add(p, in);
    }
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    printf("Time to fill an array of size: %lld : %g s\n", size, tiempo);

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    printf("Time to fill and free iterate a vector of size: %lld : %g s\n", size, tiempo);
}

void add(puntuacion val, int index)
{

    if (index >= maxElems)
    {
        if ((list = (puntuacion *)realloc(list, (size_t)(listSize * 2) * sizeof(val))) == NULL)
        {
            perror("Error al alocar memoria\n");
            return;
        }
        maxElems *= 2;
    }

    else if (index <= listSize)
    {

        if (listSize + 1 > maxElems)
        {
            if ((list = (puntuacion *)realloc(list, (size_t)(listSize * 2) * sizeof(val))) == NULL)
            {
                perror("Error al alocar memoria\n");
                return;
            }
            maxElems *= 2;
        }

        for (int i = listSize - 1; i >= index; i--)
        {
            list[i + 1] = list[i];
        }
    }
    list[index] = val;
    listSize++;
}

int binarySearchIter(puntuacion busqueda, int inf, int sup)
{
    while (inf < sup)
    {

        int midIndex = (int)floor((inf + sup) / 2);

        puntuacion mid = list[midIndex];
        if (equals(busqueda, mid))
        {
            return midIndex + 1;
        }

        if (less(busqueda, mid))
        {
            sup = midIndex - 1;
        }
        else
        {
            inf = midIndex + 1;
        }
    }

    if (inf < listSize && less(list[inf], busqueda))
    {

        return inf + 1;
    }
    else
    {

        return inf;
    }
}

int binarySearchRec(puntuacion busqueda, int inf, int sup)
{
    if (inf >= sup)
    {
        if (inf < listSize && less(list[inf], busqueda))
        {

            return inf + 1;
        }
        else
        {

            return inf;
        }
    }
    int midIndex = (int)floor((inf + sup) / 2);

    puntuacion mid = list[midIndex];
    if (equals(busqueda, mid))
    {
        return midIndex + 1;
    }

    if (less(busqueda, mid))
    {
        sup = midIndex - 1;
    }
    else
    {
        inf = midIndex + 1;
    }
    return binarySearchRec(busqueda, inf, sup);
}

int less(puntuacion a, puntuacion b)
{

    return a.time < b.time || (a.time == b.time && a.memory < b.memory);
}
int equals(puntuacion a, puntuacion b)
{
    return a.time == b.time && a.memory == b.memory;
}
