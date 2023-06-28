#include <iostream>
#include <cstring>
struct puntuationMedium
{

public:
    double time;
    int memory;
    puntuationMedium(double ti, int mem)
    {
        time = ti;
        memory = mem;
    }
    puntuationMedium()
    {
        time = 0;
        memory = 0;
    }

    friend std::ostream &operator<<(std::ostream &co, const puntuationMedium &p)
    {

        co << "Time: " << p.time << " Memory: " << p.memory << std::endl;
        return co;
    }

    bool operator<(const puntuationMedium &p) const
    {
        return (time < p.time) || (time == p.time && memory < p.memory);
    }

    bool operator>(const puntuationMedium &p) const
    {
        return (time > p.time) || (time == p.time && memory > p.memory);
    }
    bool operator>=(const puntuationMedium &p) const
    {
        return (time > p.time) || (time == p.time && memory >= p.memory);
    }
    bool operator<=(const puntuationMedium &p) const
    {
        return (time < p.time) || (time == p.time && memory <= p.memory);
    }
    bool operator==(const puntuationMedium &p) const
    {
        return time == p.time && memory == p.memory;
    }
};
