#include <iostream>
#include <cstring>
struct puntuationSmall
{

public:
    double time;

    puntuationSmall(double ti, int memory)
    {
        time = ti + memory;
    }
    puntuationSmall()
    {
        time = 0;
    }

    friend std::ostream &operator<<(std::ostream &co, const puntuationSmall &p)
    {

        co << "Time: " << p.time << std::endl;
        return co;
    }

    bool operator<(const puntuationSmall &p) const
    {
        return time < p.time;
    }

    bool operator>(const puntuationSmall &p) const
    {
        return time > p.time;
    }
    bool operator>=(const puntuationSmall &p) const
    {
        return time >= p.time;
    }
    bool operator<=(const puntuationSmall &p) const
    {
        return time <= p.time;
    }
    bool operator==(const puntuationSmall &p) const
    {
        return time == p.time;
    }
};
