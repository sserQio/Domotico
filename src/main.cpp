#include <iostream>
#include "../include/m.h"
#include "../include/cp.h"

int main() {
    M pv("Impianto Fotovoltaico", 0, 1500);
    Stime t_w_m(1,50);
    CP washing_machine("Lavatrice", 1, -2000, t_w_m);

    std::cout << "Creo oggetto Impianto Fotovoltaico" << std::endl;
    M pv("Impianto Fotovoltaico", 0, 1500);
    pv.print();
    std::cout << "Accendiamo il dispositivo" << std::endl;
    pv.set("on");
    std::cout << "Settiamo il timer del dispositivo" << std::endl;
    pv.set("17:12", "23:59");
    std::cout << "Controlliamo che l'oggetto abbia il timer impostato" << std::endl;
    pv.print();
    std::cout << "Ora rimuoviamo il timer" << std::endl;
    pv.rm();
    std::cout << "Controllo il timer sia stato rimosso" << std::endl;
    pv.print();
    std::cout << "Proviamo la funzione show" << std::endl;
    pv.show();

    std::cout << "Proviamo i metodi manuali" << std::endl;
    std::cout << "Spegniamo l'impianto fotovoltaico" << std::endl;
    pv.set("off");
    pv.print();
    return 0;
}