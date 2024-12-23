#ifndef M_H
#define M_H

#include "./device.h"

class M{
    private:
        // Orario di inizio esecuzione del dispositivo
        Time start;

        // Orario di fine esecuzione del dispositivo
        Time stop;

    public:
        // Override della funzione set
        void set(std::string device_name, std::string command);

        // Override della funzione set
        void set(std::string device_name, std::string start, std::string stop);

        // Override della funzione remove
        void rm(std::string device_name);

        // Override della funzione reset_timers
        void reset_timers();
};

#endif // M_H