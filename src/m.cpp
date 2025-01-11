#include "../include/m.h"

M::M(std::string n, int i, int c) : Device(n, i, c){
    stop.set_time("00:00");
}
// Costruttore di Copia
/*
M::M(const M& other) : Device(other), stop(other.stop) {
}

M& M::operator=(const M& other) {
    if (this != &other) {
        Device::operator=(other);
        stop = other.stop;
    }
    return *this;
}
*/

void M::set(std::string command){
    Device::set(command);
    if (command == "off"){
        stop.set_time("00:00");
    }
}

void M::set(std::string start, std::string stop){
    autoStart.set_time(start);
    this->stop.set_time(stop);
}

void M::rm(){
    Device::rm();
    stop.set_time("00:00");
}

//pensare se serve o meno perche uguale a rm()
/*void M::reset_timer(){
    autoStart.set_time("00:00");
    stop.set_time("00:00");
}
*/

Stime M::get_stop(){
    return stop;
}