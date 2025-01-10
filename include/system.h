#ifndef SYSTEM_H
#define SYSTEM_H

#include "../include/device.h"
#include "../include/stime.h"
#include "../include/m.h"
#include "../include/cp.h"

class System{
    private:
        // Limite della rete elettrica (non considerando l'impianto fotovoltaico)
        const int system_limit = 3500;

        // Produzione elettrica dell'impianto fotovoltaico
        int pv_production = 0;

    public:
        //orario del sistema
        Stime current_time{"00:00"};

        // Limite totale del sistema (rete elettrica + impianto fotovoltaico)
        int system_capacity;

        // Vettore di puntatori alla classe base Device
        std::vector<Device> devices;

        // Vector dei dispositivi CP 
        std::vector<CP> cp_devices;
        // Vector dei dispositivi M
        std::vector<M> m_devices;

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

        // Algoritmo per ordinare in ordine crescente gli oggetti devices accesi in base al parametro autostart
        void devices_sorting_on();

        // Algoritmo per ordinare in ordine crescente gli oggetti devices in base all'orario di spegnimento
        void devices_sorting_off(std::vector<Device>& v);

        // Algoritmo per ordinare in ordine crescente gli oggetti device spenti
        bool compare_devices(Device* a, Device* b);
};

#endif // SYSTEM_H