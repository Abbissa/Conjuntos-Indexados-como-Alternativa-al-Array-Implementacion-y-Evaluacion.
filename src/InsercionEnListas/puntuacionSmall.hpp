#include <iostream>
#include <cstring>
struct puntuacionSmall
{

public:
    double time;

    puntuacionSmall(double ti, int memory)
    {
        time = ti * memory;
    }

    friend std::ostream &operator<<(std::ostream &co, const puntuacionSmall &p)
    {

        co << "Time: " << p.time << std::endl;
        return co;
    }

    bool operator<(const puntuacionSmall &p) const
    {
        return time < p.time;
    }

    bool operator>(const puntuacionSmall &p) const
    {
        return time > p.time;
    }
    bool operator>=(const puntuacionSmall &p) const
    {
        return time >= p.time;
    }
    bool operator<=(const puntuacionSmall &p) const
    {
        return time <= p.time;
    }
    bool operator==(const puntuacionSmall &p) const
    {
        return time == p.time;
    }
};
