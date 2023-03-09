#include <iostream>
using namespace std;
class puntuacion

{

private:
    double time;
    int memory;

public:
    puntuacion(void);
    puntuacion(double time = 0.0, int memory = 0);
    void setTime(double time) { this->time = time; }
    void setMemory(int memory) { this->memory = memory; }
    bool operator<(const puntuacion &)const;
    friend ostream &operator<<(ostream &, const puntuacion &);
};
