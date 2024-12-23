#ifndef CP_H
#define CP_H

#include "./device.h"

class CP{
    private:
        // Durata del ciclo di accensione del dispostivo
        Time cycle_duration;

        // Richiesta di spegnimento manuale. Sempre false, ma se user vuole terminare l'esecuzione 
        // del dispositivo diventa true. auto-start (timer) si azzera ma il dispositivo rimane acceso
        bool manual_stop;

        // Override della funzione set
        void set(std::string device_name, std::string command);

        // Override della funzione set
        // Ogni volta impostiamo manual_stop = false
        void set(std::string device_name, std::string start, std::string stop);

        // Override della funzione rm
        void remove(std::string device_name);

        // Override della funzione reset_timers
        void reset_timers();

        // Impostiamo manual_stop = true e anche auto_start = 0
        void manual_reset();

        
};
#endif // CP_H