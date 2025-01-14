// Petenazzo Sergio (2066693)

#ifndef M_H
#define M_H

#include "../include/device.h"

class M : public Device{
    private:
        // Orario di fine esecuzione del dispositivo
        Stime stop;

    public:
        // Costruttore
        M(std::string n, int i, int c);

        // Override della funzione set
        void set(std::string command) override;

        // Override della funzione set
        void set(std::string start, std::string stop) override;

        // Override della funzione remove
        void rm() override;

        // Ritorna l'ora di spegnimento
        Stime get_stop();

        // Override della funzione update_total_consumption
        void update_total_consumption(Stime t) override;
};

#endif // M_H