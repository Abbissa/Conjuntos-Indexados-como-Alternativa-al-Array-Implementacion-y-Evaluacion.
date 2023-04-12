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
int binarySearchRec(puntuacion *, int, int);
int binarySearchIter(puntuacion *, int, int);
int less(puntuacion, puntuacion);
int equals(puntuacion, puntuacion);

#if (BSType == 0)
#define BS(b, inf, sup) binarySearchRec(b, inf, sup)
#define NOMBRE "StructArrayRec"
#elif (BSType == 1)
#define BS(b, inf, sup) binarySearchIter(b, inf, sup)
#define NOMBRE "StructArrayIter"
#endif

int listSize = 0;
int maxElems = 0;
puntuacion **list;
int memIncrease = 128;
int main()
{

    puntuacion *p;
    list = (puntuacion **)calloc(memIncrease, sizeof(p));
    maxElems = memIncrease;
    srand(time(NULL));

    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    double time;
    int size = 0;
    while (scanf("%f", &time) == 1)
    {

        p = (puntuacion *)malloc(sizeof(puntuacion));
        if (!p)
        {
            free(p);
            return 1;
        }
        p->time = time;
        scanf("%d", &p->memory);

        int in = binarySearchIter(p, 0, listSize);
        add(p, in);
        size++;
    }
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    puntuacion *p2;
    p = list[0];
    for (size_t i = 1; i < size; i++)
    {
        p2 = list[i];
        if (less(*p2, *p))
        {
            perror("ERROR: wrong output order");
            return 1;
        }
        p = p2;
    }
    printf("%s,%d,%g\n", NOMBRE, size, tiempo);

    // gettimeofday(&tf, NULL);
    // tiempo = (tf.tv_sec - ti.tv_sec) + (tf.tv_usec - ti.tv_usec) / 1000000.0;
    // printf("Time to fill and free iterate a vector of size: %lld : %g s\n", size, tiempo);
}

void add(puntuacion *val, int index)
{

    if (index >= maxElems)
    {
        if ((list = (puntuacion **)realloc(list, (size_t)(listSize * 2) * sizeof(val))) == NULL)
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
            if ((list = (puntuacion **)realloc(list, (size_t)(listSize * 2) * sizeof(val))) == NULL)
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

int binarySearchRec(puntuacion *busqueda, int inf, int sup)
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
    return binarySearchRec(busqueda, inf, sup);
}
int binarySearchIter(puntuacion *busqueda, int inf, int sup)
{

    while (inf < sup)
    {

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
    }

    if (inf < listSize && less(*list[inf], *busqueda))
    {

        return inf + 1;
    }
    else
    {

        return inf;
    }
}

int less(puntuacion a, puntuacion b)
{

    return a.time < b.time || (a.time == b.time && a.memory < b.memory);
}
int equals(puntuacion a, puntuacion b)
{
    return a.time == b.time && a.memory == b.memory;
}
