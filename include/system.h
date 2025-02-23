// Castellini Camilla (2103044)

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

        // Vettore di dispositivi accesi necessario per la politica di rimpiazzo in caso di sovraccarico
        std::vector<Device*> devices_on;
 
    public:
        // Costruttore
        System();
        
        // Orario del sistema
        Stime current_time{"00:00"};

        // Limite totale del sistema (rete elettrica + impianto fotovoltaico)
        int system_capacity;

        // Vettore di puntatori alla classe base Device
        std::vector<Device*> devices;

        // Funzione per cercare un dispositivo nel sistema
        Device* search_device(std::string device_name);

        // Mostra la lista di tutti i dispositivi (attivi e inattivi) con la produzione/consumo
        // energetico di ciascuno dalle 00:00 al momento di invio del comando. Inoltre
        // mostra la produzione/consumo energetico totale del sistema dalle 00:00 al momento
        // di invio del comando
        void show_all();

        // Salta a una specifica ora del giorno
        double set_time(std::string t);

        // Porta l'orario del sistema a 00:00 e riporta i dispositivi alle condizioni iniziali
        void reset_time();

        // Rimuove tutti i timer ma i dispositivi mantengono il loro stato di accensione
        void reset_timers();

        // - Riporta il sistema alle condizioni iniziali
        // - Orario impostato a 00:00
        // - Timer vengono rimossi
        // - Dispositivi spenti
        void reset_all();

        // Algoritmo per ordinare in ordine crescente gli oggetti devices accesi in base al parametro autoStart
        void devices_sorting_on();

        // Algoritmo per ordinare in ordine crescente gli oggetti devices in base all'orario di spegnimento
        void devices_sorting_off(std::vector<Device*>& v);

        // Algoritmo per ordinare in ordine crescente gli oggetti device spenti
        bool compare_devices(Device* a, Device* b);

        // 
        // void add_device(Device* d);

        // Ritorna il system_limit
        int get_system_limit();
};

#endif // SYSTEM_H