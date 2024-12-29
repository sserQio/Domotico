#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time{
    private:
        int hours;
        int minutes;

    public:
        // Costruttore di default
        Time();

        // Costruttore. Il parametro passato è una stringa che indica l'ora in formato hh:mm
        Time(std::string t);

        // Stampa l'orario corrente
        // PROBLEMA: L'ora viene scritta come 0:0 e non 00:00
        void print_time();

        // Modifica l'orario con uno a scelta
        void change_time(std::string h, std::string m);

        // Imposta orario dato l'orario come stringa unica
        void set_time(std::string time);
};

#endif // TIME_H