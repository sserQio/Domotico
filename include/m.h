#ifndef M_H
#define M_H

#include "./device.h"

class M : public Device{
    private:
        // Orario di inizio esecuzione del dispositivo
        // Time start;

        // Orario di fine esecuzione del dispositivo
        Time stop;

    public:
        // Costruttore
        M(std::string n, int i, int c);

        // Costruttore di copia
        M(const M& other);

        // Operatore di assegnazione di copia
        M& operator=(const M& other);
        
        // Override della funzione set
        void set(std::string command) override;

        // Override della funzione set
        void set(std::string start, std::string stop) override;

        // Override della funzione remove
        void rm() override;

        // Override della funzione reset_timer
        //void reset_timer() override;

        // Ritorna l'ora di spegnimento
        Time get_stop();
};

#endif // M_H