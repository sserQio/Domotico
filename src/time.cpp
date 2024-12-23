#include "../include/time.h"

Time::Time(std::string t){
    // Inizializza le variabili hours e minutes con i valori contenuti nella stringa t
    hours = std::stoi(t.substr(0, 2));
    minutes = std::stoi(t.substr(3, 2));
}

void Time::print_time(){
    // Stampa l'ora
    std::cout << "Orario corrente: " << hours << ":" << minutes << std::endl;
}

void Time::change_time(std::string h, std::string m){
    // Modifica l'ora con i valori passati come parametri
    hours = std::stoi(h);
    minutes = std::stoi(m);
}