#include <iostream>
#include "../include/m.h"
#include "../include/cp.h"
#include "../include/system.h"

int main() {
    
    System casa{};
    std::string name = "Lavatrice";
    Device* d = nullptr;
    d = casa.search_device(name);
    std::cout << "Qui viene scritto Lavatrice -> " << d->get_name() << std::endl;
    CP* l = dynamic_cast<CP*>(d);
    std::cout << "La durata del ciclo è: " << l->get_duration() << std::endl;

    name = "Frigorifero";
    Device* d2 = nullptr;
    d2 = casa.search_device(name);
    std::cout << "Qui viene scritto Frigorifero -> " << d2->get_name() << std::endl;
    M* t = dynamic_cast<M*>(d2);
    std::cout << "L'orario di spegnimento è: " << t->get_stop() << std::endl;
    std::cout << "Il consumo di Frigorifero è: " << d2->get_consumption() << std::endl;

    l -> set("on");
    std::cout << "Ora la Lavatrice è accesa" << std::endl;
    std::cout << "Lo è veramente? Lo stato è: " << l -> get_is_on() << std::endl;
    

    t -> set("on");
    std::cout << "Ora il Frigorifero è acceso" << std::endl;
    std::cout << "Lo è veramente? Lo stato è: " << t -> get_is_on() << std::endl;
    t -> set("19:30", "20:00");
    std::cout << "Ora il Frigorifero si spegne alle " << t -> get_stop() << std::endl;
    t -> rm();
    t -> get_autoStart().print_time();


    return 0;
}