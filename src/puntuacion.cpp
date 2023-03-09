#include "puntuacion.h"

puntuacion::puntuacion(void)
{
    time = 0;
    memory = 0;
}
puntuacion::puntuacion(double ti, int mem)
{
    time = ti;
    memory = mem;
}

ostream &operator<<(ostream &co, const puntuacion &p)
{

    co << "Time: " << p.time << " Memory: " << p.memory << endl;
    return co;
}

bool puntuacion::operator<(const puntuacion &p)const
{
    if (time < p.time)
        return true;

    if (time==p.time&&memory < p.memory)
        return true;
    return false;
}