#include "../include/time.h"

Time::Time(){
    hours = 0;
    minutes = 0;
}
Time ::Time(int h, int m){
    hours=h;
    minutes=m;
}
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

void Time::set_time(std::string time){
    std::string hours = time.substr(0, 2);
    std::string minutes = time.substr(3, 2);
    change_time(hours, minutes); 
}

int Time::get_hours(){
    return hours;
}

int Time::get_minutes(){
    return minutes;
}

Time Time::operator+(const Time& t) const {
    int tot_min = this->minutes + t.minutes;
    int tot_hours = this->hours + t.hours;

    // Nel caso in cui la somma dei minuti sia superiore a 60, calcoliamo 
    // quante ore ci sono in quei minuti e le aggiungiamo al conteggio delle ore
    tot_hours += tot_min/60;

    // Gestiamo il ciclo 24h
    tot_hours%=24;

    // Data la somma dei minuti, i soli minuti sono il resto della divisione per 60
    if (tot_min < 0) {
        tot_min += 60;
        tot_hours -= 1;
    }
    tot_min = tot_min % 60;

    return Time(tot_hours, tot_min);
}

Time Time::operator-(const Time& t) const {
    int tot_min = this->minutes - t.minutes;
    int tot_hours = this->hours - t.hours;

    // Nel caso in cui la sootrazione dei minuti sia inferiore a 0, sottraiamo 
    // un'ora e calcoliamo i minuti corretti
    if (tot_min < 0){
        tot_min += 60;
        tot_hours--;
    }
    return Time(tot_hours, tot_min);
}

bool Time::operator>(const Time& t) const{
    if(this -> hours > t.hours) return true;
    if((this -> hours == t.hours) && (this -> minutes > t.minutes)) return true;
    return false;
}