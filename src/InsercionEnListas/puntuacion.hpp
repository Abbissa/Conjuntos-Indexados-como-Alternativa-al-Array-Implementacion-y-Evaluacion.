#include <iostream>
class puntuacion
{

private:
    double time;
    int memory;

public:
    puntuacion();
    puntuacion(double time = 0.0, int memory = 0);
    bool operator<(const puntuacion &)const;
    friend std::ostream &operator<<(std::ostream &, const puntuacion &);
};
