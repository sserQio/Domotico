#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time{
    private:
        int hours;
        int minutes;

    public:
        // Costruttore. Il parametro passato è una stringa che indica l'ora in formato hh:mm
        Time(std::string t);

        // Stampa l'orario corrente
        void print_time();

        // Modifica l'orario con uno a scelta
        void change_time(std::string h, std::string m);

        // Imposta orario dato l'orario come stringa unica
        void Time::set_time(std::string time);
};

#endif // TIME_H