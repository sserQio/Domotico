#include "../include/device.h"

Device::Device(std::string n, int i, double c):
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

