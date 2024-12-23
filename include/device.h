#ifndef DEVICE_H
#define DEVICE_H

#include "./time.h"
#include <vector>

class Device{
    private:
        // Nome del dispositivo
        std::string name;

        // ID numerico unico del dispositivo
        int id;

        // Consumo del dispositivo
        double consumption;

        // Orario di inizio di esecuzione automatico di un dispositivo
        Time autoStart;

        // Varibile che definisce l'accensione o meno di un dispositivo
        bool is_on;

    public:
        // Costruttore
        Device(std::string n, int i, double c);
        
        // Funzione per accendere e spegnere un dispositivo
        virtual void set(std::string device_name, std::string command);

        // Funzione per impostare specifici orari di accensione e spegnimento del dispositivo
        virtual void set(std::string device_name, std::string start, std::string stop);

        // auto-start si azzera
        virtual void rm(std::string device_name);

        // Mostra a schermo produzione/consumo energetico di un dispositivo specificato
        void show(std::string device_name);

        // Rimuove il timer di tutti i dispositivi. I dispositivi rimangono nello stato attuale
        virtual void reset_timers();

        // Disabilita il costruttore di copia
        Device::Device(const Device&) = delete;

        // Disabilita l'operatore di assegnamento
        Device& Device::operator=(const Device&) = delete;
};

#endif // DEVICE_H