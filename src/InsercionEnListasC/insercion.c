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
void add(puntuacion *, int);
int binarySearch(puntuacion *, int, int);
int less(puntuacion, puntuacion);
int equals(puntuacion, puntuacion);

int listSize = 0;
int maxElems = 0;
puntuacion **list;
int memIncrease = 128;
int main()
{
    size_t size = 100000;
    puntuacion *a;
    list = (puntuacion **)calloc(memIncrease, sizeof(a));
    maxElems = memIncrease;
    srand(time(NULL));

    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);

    for (size_t i = 0; i < size; i++)
    {

        a = (puntuacion *)malloc(sizeof(puntuacion));
        a->time = (double)(rand() % 100);
        a->memory = rand() % 100;

        int in = binarySearch(a, 0, listSize);

        add(a, in);
    }
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    printf("Time to fill an array of size: %lld : %g s\n", size, tiempo);

    for (size_t i = 0; i < size; i++)
    {
        free(list[i]);
    }
    free(list);
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    printf("Time to fill and free iterate a vector of size: %lld : %g s\n", size, tiempo);
}

void add(puntuacion *val, int index)
{

    if (index >= maxElems)
    {
        if ((list = realloc(list, (size_t)(listSize + memIncrease) * sizeof(val))) == NULL)
        {
            perror("Error al alocar memoria\n");
            return;
        }
        maxElems += memIncrease;
    }

    else if (index <= listSize)
    {

        if (listSize + 1 > maxElems)
        {
            if ((list = realloc(list, (size_t)(listSize + memIncrease) * sizeof(val))) == NULL)
            {
                perror("Error al alocar memoria\n");
                return;
            }
            maxElems += memIncrease;
        }

        for (int i = listSize - 1; i >= index; i--)
        {
            list[i + 1] = list[i];
        }
    }
    list[index] = val;
    listSize++;
}

int binarySearch(puntuacion *busqueda, int inf, int sup)
{

    if (inf >= sup)
    {
        if (inf < listSize && less(*list[inf], *busqueda))
        {

            return inf + 1;
        }
        else
        {

            return inf;
        }
    }

    int midIndex = (int)floor((inf + sup) / 2);

    puntuacion mid = *list[midIndex];
    if (equals(*busqueda, mid))
    {
        return midIndex + 1;
    }

    if (less(*busqueda, mid))
    {
        sup = midIndex - 1;
    }
    else
    {
        inf = midIndex + 1;
    }
    return binarySearch(busqueda, inf, sup);
}

int less(puntuacion a, puntuacion b)
{

    return a.time < b.time || (a.time == b.time && a.memory < b.memory);
}
int equals(puntuacion a, puntuacion b)
{
    return a.time == b.time && a.memory == b.memory;
}
