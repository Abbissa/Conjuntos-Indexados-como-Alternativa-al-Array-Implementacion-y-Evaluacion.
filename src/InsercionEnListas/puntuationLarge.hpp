#include <iostream>
#include <cstring>
struct puntuationLarge
{

public:
    double time;
    int memory;
    char name[50];
    puntuationLarge(double ti, int mem)
    {
        time = ti;
        memory = mem;
        std::string nameStr = "puntuation:" + std::to_string(ti) + "-" + std::to_string(mem);
        std::strcpy(name, nameStr.c_str());
    }
    puntuationLarge()
    {
        time = 0;
        memory = 0;
        std::strcpy(name, "");
    }

    friend std::ostream &operator<<(std::ostream &co, const puntuationLarge &p)
    {

        co << "Time: " << p.time << " Memory: " << p.memory << std::endl;
        return co;
    }

    bool operator<(const puntuationLarge &p) const
    {
        return time < p.time || (time == p.time && memory < p.memory);
    }

    bool operator>(const puntuationLarge &p) const
    {
        return time > p.time || (time == p.time && memory > p.memory);
    }
    bool operator>=(const puntuationLarge &p) const
    {
        return time > p.time || (time == p.time && memory >= p.memory);
    }
    bool operator<=(const puntuationLarge &p) const
    {
        return time < p.time || (time == p.time && memory <= p.memory);
    }
    bool operator==(const puntuationLarge &p) const
    {
        return time == p.time && memory == p.memory;
    }
};
