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
#define NOMBRE "PtrArrayRec"
#elif (BSType == 1)
#define BS(b, inf, sup) binarySearchIter(b, inf, sup)
#define NOMBRE "PtrArrayIter"
#endif

int listSize = 0;
int maxElems = 0;
puntuacion *list;
size_t baseMem = 128;
int main()
{

    puntuacion p;
    list = (puntuacion *)calloc(baseMem, sizeof(puntuacion));
    maxElems = baseMem;

    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    int size = 0;
    while (scanf("%lf", &p.time) == 1)
    {

        scanf("%d", &p.memory);
        int in = BS(p, 0, listSize);
        add(p, in);
        size++;
    }
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;

    puntuacion p2;
    p = list[0];
    for (size_t i = 1; i < size; i++)
    {
        p2 = list[i];
        if (less(p2, p))
        {
            perror("ERROR: La lista no esta ordenada\n");
            return 1;
        }
        p = p2;
    }

    printf("%s,%d,%g\n", NOMBRE, size, tiempo);
}

void add(puntuacion val, int index)
{

    if (index >= maxElems)
    {
        if ((list = (puntuacion *)realloc(list, (size_t)(listSize * 2) * sizeof(val))) == NULL)
        {
            perror("Error al reservar memoria\n");
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
                perror("Error al reservar memoria\n");
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
