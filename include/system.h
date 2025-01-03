#ifndef SYSTEM_H
#define SYSTEM_H

#include "./device.h"
#include "./time.h"
#include "./m.h"
#include "./cp.h"

class System{
    private:
        // Limite della rete elettrica (non considerando l'impianto fotovoltaico)
        const int system_limit = 3500;

        // Produzione elettrica dell'impianto fotovoltaico
        int pv_production = 0;

    public:
        //orario del sistema
        Time current_time{"00:00"};

        // Limite totale del sistema (rete elettrica + impianto fotovoltaico)
        int system_capacity;

        // Vector dei dispositivi cp 
        std::vector<Device> cp_devices;
        // Vector dei dispositivi m
        std::vector<Device> m_devices;

        // Funzione per cercare un dispositivo nel sistema
        M* search_m_device(std::string device_name);
        CP* search_cp_device(std::string device_name);

        // Mostra la lista di tutti i dispositivi (attivi e inattivi) con la produzione/consumo
        // energetico di ciascuno dalle 00:00 al momento di invio del comando. Inoltre
        // mostra la produzione/consumo energetico totale del sistema dalle 00:00 al momento
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