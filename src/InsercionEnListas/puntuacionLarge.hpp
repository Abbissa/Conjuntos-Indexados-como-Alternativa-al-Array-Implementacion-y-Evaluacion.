#include <iostream>
#include <cstring>
class puntuacionLarge
{

public:
    double time;
    int memory;
    char name[35];
    puntuacionLarge(double ti, int mem)
    {
        time = ti;
        memory = mem;
        std::string nameStr = "puntuacion:" + std::to_string(ti) + "-" + std::to_string(mem);
        std::strcpy(name, nameStr.c_str());
    }

    friend std::ostream &operator<<(std::ostream &co, const puntuacionLarge &p)
    {

        co << "Time: " << p.time << " Memory: " << p.memory << std::endl;
        return co;
    }

    bool operator<(const puntuacionLarge &p) const
    {
        return time < p.time || (time == p.time && memory < p.memory);
    }

    bool operator>(const puntuacionLarge &p) const
    {
        return time > p.time || (time == p.time && memory > p.memory);
    }
    bool operator>=(const puntuacionLarge &p) const
    {
        return time > p.time || (time == p.time && memory >= p.memory);
    }
    bool operator<=(const puntuacionLarge &p) const
    {
        return time < p.time || (time == p.time && memory <= p.memory);
    }
    bool operator==(const puntuacionLarge &p) const
    {
        return time == p.time && memory == p.memory;
    }
};