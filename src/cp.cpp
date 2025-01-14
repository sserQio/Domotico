#include "../include/cp.h"

CP::CP(std:: string n, int i, int c, Stime cd): Device(n, i, c){
    // cycle_duration e cd puntano alla stessa area di memoria
    cycle_duration = cd;
    // manual_stop = false;
}

// Costruttore di Copia
/*
CP::CP(const CP& other) : Device(other), cycle_duration(other.cycle_duration) {
}

CP& CP::operator=(const CP& other) {
    if (this != &other) {
        Device::operator=(other);
        cycle_duration = other.cycle_duration;
    }
    return *this;
}
*/

void CP::set(std::string command){
    Device::set(command);
    // Se (autostart + cycle duraion) > current_time allora: 
    // manual stop = true
}

void CP::set(std::string start, std::string stop){
    autoStart.set_time(start);
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

void CP::update_total_consumption(Stime t){
    total_consumption += consumption;
}