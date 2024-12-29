#ifndef M_H
#define M_H

#include "./device.h"

class M : public Device{
    private:
        // Orario di inizio esecuzione del dispositivo
        Time start;

        // Orario di fine esecuzione del dispositivo
        Time stop;

    public:
        // Override della funzione set
        void set(std::string command) override;

        // Override della funzione set
        void set(std::string start, std::string stop) override;

        // Override della funzione remove
        void rm() override;

        // Override della funzione reset_timers
        void reset_timers() override;
};

#endif // M_H