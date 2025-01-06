#include "../include/cp.h"

CP::CP(std:: string n, int i, int c, Time cd): Device(n, i, c){

    // cycle_duration e cd puntano alla stessa area di memoria
    cycle_duration = cd;
    // manual_stop = false;
}

void CP::set(std::string command){
    Device::set(command);
    // Se (autostrat + cycle duraion) > current_time allora: 
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

Time CP::get_duration(){
    return cycle_duration;
}