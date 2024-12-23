#ifndef CP_H
#define CP_H

#include "./device.h"

class CP : public Device{
    private:
        // Durata del ciclo di accensione del dispostivo
        Time cycle_duration;

        // Richiesta di spegnimento manuale. Sempre false, ma se user vuole terminare l'esecuzione 
        // del dispositivo diventa true. auto-start (timer) si azzera ma il dispositivo rimane acceso
        bool manual_stop;

        // Override della funzione set
        void set(std::string device_name, std::string command) override;

        // Override della funzione set
        // Ogni volta impostiamo manual_stop = false
        void set(std::string device_name, std::string start, std::string stop) override;

        // Override della funzione rm
        void rm(std::string device_name) override;

        // Override della funzione reset_timers
        void reset_timers() override;

        // Impostiamo manual_stop = true e anche auto_start = 0
        void manual_reset();

        
};
#endif // CP_H