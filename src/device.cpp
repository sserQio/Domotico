#include "../include/device.h"

Device::Device(std::string n, int i, int c):
    name {n},
    id {i},
    consumption {c},
    autoStart {"00:00"},
    is_on {false}
{}

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
