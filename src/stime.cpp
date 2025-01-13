#include "../include/stime.h"

Stime::Stime(){
    hours = 0;
    minutes = 0;
}
Stime::Stime(int h, int m){
    hours=h;
    minutes=m;
}
Stime::Stime(std::string t){
    // Inizializza le variabili hours e minutes con i valori contenuti nella stringa t
    hours = std::stoi(t.substr(0, 2));
    minutes = std::stoi(t.substr(3, 2));
}

void Stime::print_time(){
    // Stampa l'ora corrente
    std::cout << "[" << hours << ":" << minutes << "] " << std::endl;
}

void Stime::change_time(std::string h, std::string m){
    // Modifica l'ora con i valori passati come parametri
    hours = std::stoi(h);
    minutes = std::stoi(m);
}

void Stime::set_time(std::string time){
    std::string hours = time.substr(0, 2);
    std::string minutes = time.substr(3, 2);
    change_time(hours, minutes); 
}

int Stime::get_hours(){
    return hours;
}

int Stime::get_minutes(){
    return minutes;
}

Stime Stime::operator+(const Stime& t) const {
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

    return Stime(tot_hours, tot_min);
}

Stime Stime::operator-(const Stime& t) const {
    int tot_min = this->minutes - t.minutes;
    int tot_hours = this->hours - t.hours;

    // Nel caso in cui la sootrazione dei minuti sia inferiore a 0, sottraiamo 
    // un'ora e calcoliamo i minuti corretti
    if (tot_min < 0){
        tot_min += 60;
        tot_hours--;
    }
    return Stime(tot_hours, tot_min);
}

bool Stime::operator>(const Stime& t) const{
    if(this -> hours > t.hours) return true;
    if((this -> hours == t.hours) && (this -> minutes > t.minutes)) return true;
    return false;
}

bool Stime::operator<(const Stime& t) const{
    if(this -> hours < t.hours) return true;
    if((this -> hours == t.hours) && (this -> minutes < t.minutes)) return true;
    return false;
}

bool Stime::operator!=(const Stime& t) const{
    if (hours != t.hours || minutes != t.minutes) return true;
    else return false;
}

bool Stime::operator<=(const Stime& t) const{
    if(this -> hours <= t.hours) return true;
    if((this -> hours == t.hours) && (this -> minutes <= t.minutes)) return true;
    return false;
}

// Essendo friend non appartiene alla classe quindi non usa l'operatore di risoluzione di scope ::
std::ostream& operator<<(std::ostream& os, const Stime& time) {
            os << std::setw(2) << std::setfill('0') << time.hours << ":"
               << std::setw(2) << std::setfill('0') << time.minutes;
            return os;
}