// Petenazzo Sergio (2066693)

#ifndef CP_H
#define CP_H

#include "../include/device.h"

class CP : public Device{

    private:
        // Durata del ciclo di accensione del dispostivo
        Stime cycle_duration;

    public:
        CP(std:: string n, int i, int c, Stime cd);
        
        // Override della funzione set
        void set(std::string command) override;

        // Override della funzione set
        // Ogni volta impostiamo manual_stop = false
        void set(std::string start, std::string stop) override;

        // Override della funzione rm
        void rm() override;

        // Ritorna la durata del ciclo di esecuzione del dispositivo
        Stime get_duration();

        // Override della funzoine update_total_consumption
        void update_total_consumption(Stime t) override;

        // Aggiora il consumo totale nel caso in cui un dispositivo CP non abbia finito il ciclo
        void set_total_consumption(Stime t);
};
#endif // CP_H