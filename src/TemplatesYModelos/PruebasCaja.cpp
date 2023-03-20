#include <iostream>
#include "caja.hpp"
#include "limon.hpp"
#include "zapato.hpp"

using namespace std;

int main()
{

    Caja<Limon> cajaLimon(20);
    Caja<Zapato> cajaZapato(40);

    // Caja<int> cajaNoVal(1); caja no valida

    Zapato zp1;
    Limon l1;
    l1.size = 21;
    zp1.size = 20;
    cout << cajaLimon << endl;
    cout << cajaZapato << endl;

    cajaZapato.addItem(zp1);
    cajaLimon.addItem(l1);
    cout << cajaZapato << endl;

    // cajaLimon1.addItem(zp1);  No compila
}