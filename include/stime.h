// Petenazzo Sergio (2066693)

#ifndef STIME_H
#define STIME_H

#include <iostream>
#include <string>
#include <iomanip>

class Stime{
    private:
        int hours;
        int minutes;

    public:
        // Costruttore di default
        Stime();

        //Costruttore che accetta due int
        Stime(int h, int m);

        // Costruttore. Il parametro passato è una stringa che indica l'ora in formato hh:mm
        Stime(std::string t);

        // Modifica l'orario con uno a scelta
        void change_time(std::string h, std::string m);

        // Imposta orario dato l'orario come stringa unica
        void set_time(std::string time);

        // Ritorna il numero di ore
        int get_hours();

        // Ritorna il numero di minuti
        int get_minutes(); 

        // Overloading dell'operatore + 
        // Pensare se mettere const prima del tipo ritornato Stime
        Stime operator+(const Stime& t) const;

        // Overloading dell'operatore -
        Stime operator-(const Stime& t) const;

        // Overloading dell'operatore >
        bool operator>(const Stime& t) const;

        // Overloading dell'operatore <
        bool operator<(const Stime& t) const;

        // Overloading dell'operatore !=
        bool operator!=(const Stime& t) const;

        // Overloading dell'operatore <=
        bool operator<=(const Stime& t) const;

        // Overloading dell'operatore <<
        friend std::ostream& operator<<(std::ostream& os, const Stime& time);
};

#endif // STIME_H