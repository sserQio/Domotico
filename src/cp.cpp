#include "../include/cp.h"

CP::CP(std:: string n, int i, int c, Stime cd): Device(n, i, c){
    // cycle_duration e cd puntano alla stessa area di memoria
    cycle_duration = cd;
    // manual_stop = false;
}

CP::CP(const CP& other) : Device(other), cycle_duration(other.cycle_duration) {
}

CP& CP::operator=(const CP& other) {
    if (this != &other) {
        Device::operator=(other);
        cycle_duration = other.cycle_duration;
    }
    return *this;
}

void CP::set(std::string command){
    Device::set(command);
    // Se (autostart + cycle duraion) > current_time allora: 
    // manual stop = true
}

void CP::set(std::string start, std::string stop){
    autoStart.set_time(start);
    // manual_stop = false;
}

void CP::rm(){
     Device::rm();
}

// Valutare in seguito la sua utilità
/*
void CP::reset_timer(){
    rm();
}
*/

Stime CP::get_duration(){
    return cycle_duration;
}