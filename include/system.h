#ifndef SYSTEM_H
#define SYSTEM_H

#include "./device.h"
#include "./time.h"

class System{
    private:
        // Limite della rete elettrica (non considerando l'impianto fotovoltaico)
        const int system_limit;

        // Produzione elettrica dell'impianto fotovoltaico
        int pv_production;

    public:
        // Limite totale del sistema (rete elettrica + impianto fotovoltaico)
        int system_capacity;

        // Vector dei dispositivi esistenti
        std::vector<Device> devices;

        // Funzione per cercare un dispositivo nel sistema
        Device search_device(std::string device_name);

        // Mostra la lista di tutti i dispositivi (attivi e inattivi) con la produzione/consumo
        // energetico di ciascuno dalle 00:00 al momento di invio del comando. Inoltre
        //mostra la produzione/consumo energetico totale del sistema dalle 00:00 al momento
        // di invio del comando
        void show();

        // Salta a una specifica ora del giorno
        void set_time(std::string time);

        // Porta l'orario del sistema a 00:00 e riporta i dispositivi alle condizioni iniziali
        void reset_time();

        // - Sistema alle condizioni iniziali
        // - Orario impostato a 00:00
        // - Timer rimossi
        // - Dispositivi spenti
        void reset_all();
};

#endif // SYSTEM_H