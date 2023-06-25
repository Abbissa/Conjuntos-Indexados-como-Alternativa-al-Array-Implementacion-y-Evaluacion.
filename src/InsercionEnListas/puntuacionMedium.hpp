#include <iostream>
#include <cstring>
struct puntuacionMedium
{

public:
    double time;
    int memory;
    puntuacionMedium(double ti, int mem)
    {
        time = ti;
        memory = mem;
    }
    puntuacionMedium()
    {
        time = 0;
        memory = 0;
    }

    friend std::ostream &operator<<(std::ostream &co, const puntuacionMedium &p)
    {

        co << "Time: " << p.time << " Memory: " << p.memory << std::endl;
        return co;
    }

    bool operator<(const puntuacionMedium &p) const
    {
        return (time < p.time) || (time == p.time && memory < p.memory);
    }

    bool operator>(const puntuacionMedium &p) const
    {
        return (time > p.time) || (time == p.time && memory > p.memory);
    }
    bool operator>=(const puntuacionMedium &p) const
    {
        return (time > p.time) || (time == p.time && memory >= p.memory);
    }
    bool operator<=(const puntuacionMedium &p) const
    {
        return (time < p.time) || (time == p.time && memory <= p.memory);
    }
    bool operator==(const puntuacionMedium &p) const
    {
        return time == p.time && memory == p.memory;
    }
};
