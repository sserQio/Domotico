#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time{
    private:
        int hours;
        int minutes;

    public:
        // Stampa l'orario corrente
        void print_time();

        // Modifica l'orario con uno a scelta
        void change_time(std::string h, std::string m);
};

#endif // TIME_H