// Petenazzo Sergio (2066693)

#include "../include/cp.h"

CP::CP(std:: string n, int i, int c, Stime cd): Device(n, i, c){
    // cycle_duration e cd puntano alla stessa area di memoria
    cycle_duration = cd;
}

void CP::set(std::string command){
    Device::set(command);
}

void CP::set(std::string start, std::string stop){
    autoStart.set_time(start);
}

void CP::rm(){
    Device::rm();
}

Stime CP::get_duration(){
    return cycle_duration;
}

void CP::update_total_consumption(Stime t){
    total_consumption += consumption;
}

void CP::set_total_consumption(Stime t){
    t = t - autoStart;
    total_consumption += consumption * (t.get_hours() + ((double)t.get_minutes()/60));
}