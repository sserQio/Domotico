#include "../include/device.h"

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
    if (name == "Impianto Fotovoltaico") std::cout << name << " produce: " << consumption << std::endl;
    else std::cout << name << " consuma: " << consumption << std::endl;
}

void Device::print(){
    std::cout << "Nome: " << name << ", id: " << id << ", consumption: " << consumption << ", is_on " << is_on << ", ";
    autoStart.print_time();
}

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

void Device::update_total_consumption(Stime t){
    //t = t - autoStart;
    //std::cout << "Il tempo t in update_total_consumption: " << t << std::endl;
    //total_consumption += consumption * (t.get_hours() + ((double)t.get_minutes()/60));
}