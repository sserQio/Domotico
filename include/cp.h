#ifndef CP_H
#define CP_H

#include "../include/device.h"

class CP : public Device{

    private:
        // Durata del ciclo di accensione del dispostivo
        Stime cycle_duration;

        // Richiesta di spegnimento manuale. Sempre false, ma se user vuole terminare l'esecuzione 
        // del dispositivo diventa true. auto-start (timer) si azzera ma il dispositivo rimane acceso
        // bool manual_stop;

    public:
        CP(std:: string n, int i, int c, Stime cd);

        // Costruttore di copia
        // CP(const CP& other);

        // Operatore di assegnazione di copia
        // CP& operator=(const CP& other);
        
        // Override della funzione set
        void set(std::string command) override;

        // Override della funzione set
        // Ogni volta impostiamo manual_stop = false
        void set(std::string start, std::string stop) override;

        // Override della funzione rm
        void rm() override;

        // Override della funzione reset_timers
        //void reset_timer() override;

        // Impostiamo manual_stop = true e anche auto_start = 0
        // void manual_reset();

        // Ritorna la durata del ciclo di esecuzione del dispositivo
        Stime get_duration();

        // Override della funzoine update_total_consumption
        void update_total_consumption(Stime t) override;
};
#endif // CP_H