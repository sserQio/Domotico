// Castellini Camilla (2103044)

#include "../include/device.h"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

Device::Device(std::string n, int i, int c):
    name {n},
    id {i},
    consumption {c},
    autoStart {"00:00"},
    is_on {false},
    total_consumption{0}
{}

// Costruttore di copia
Device::Device(const Device& other) :
    name {other.name},
    id {other.id},
    consumption {other.consumption},
    autoStart {other.autoStart},
    is_on {other.is_on},
    total_consumption {other.total_consumption}
{}

// Operatore di assegnazione di copia
Device& Device::operator=(const Device& other) {
    if (this != &other) {
        name = other.name;
        id = other.id;
        consumption = other.consumption;
        autoStart = other.autoStart;
        is_on = other.is_on;
        total_consumption = other.total_consumption;
    }
    return *this;
}

void Device::set(std::string command){
    if (command == "on"){
        is_on = true;
    } else {
        is_on = false;
        autoStart.set_time("00:00");

    }
}

void Device::set(std::string start, std::string stop){
    autoStart.set_time(start);
}

void Device::rm(){
    autoStart.set_time("00:00");
}

void Device::show(){
    if (name == "Impianto fotovoltaico") std::cout << name << " produce: " << GREEN << consumption << " Wh" << RESET << std::endl;
    else std::cout << name << " consuma: " << RED << consumption << " Wh" << RESET << std::endl;
}

//void Device::print(){
//    std::cout << "Nome: " << name << ", id: " << id << ", consumption: " << consumption << ", is_on " << is_on << ", ";
//    std::cout << "["
//}

std::string Device::get_name(){
    return name;
}

int Device::get_consumption(){
    return consumption;
}

bool Device::get_is_on(){
    return is_on;
}

Stime Device::get_autoStart(){
    return autoStart;
}

int Device::get_total_consumption(){
    return total_consumption;
}

// Funzione scritta virtuale per non fare altri downcasting in modo che i CP e gli M salvati in oggetti Device
// chiamino "la loro funzione update_total_consumption".
// Per come era stato pensato il programma non è stato possibile porla virtuale pura
void Device::update_total_consumption(Stime t){}

void Device::reset_total_consumption(){
    total_consumption = 0;
}