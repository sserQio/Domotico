// Petenazzo Sergio (2066693)

#include "../include/m.h"

M::M(std::string n, int i, int c) : Device(n, i, c){
    stop.set_time("00:00");
}

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

Stime M::get_stop(){
    return stop;
}

void M::update_total_consumption(Stime t){
    t = t - autoStart;
    total_consumption += consumption * (t.get_hours() + ((double)t.get_minutes()/60));
}