// Barison Alessia (2103043)

#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>
#include <vector>
#include "../include/stime.h"

class Device{
    protected:
        // Nome del dispositivo
        std::string name;

        // ID numerico unico del dispositivo
        int id;

        // Consumo del dispositivo
        int consumption;

        // Varibile che definisce l'accensione o meno di un dispositivo
        bool is_on;

        // Variabile che tiene traccia del consumo totale di un dispositivo
        double total_consumption;

        // Orario di inizio di esecuzione automatico di un dispositivo
        // Questo parametro è comune a tutti i dispositivi, indipendentemente da M o CP
        Stime autoStart;

    public:
        // Costruttore
        Device(std::string n, int i, int c);

        // Costruttore di copia
        Device(const Device& other);

        // Operatore di assegnazione di copia
        Device& operator=(const Device& other);
        
        // Funzione per accendere e spegnere un dispositivo
        virtual void set(std::string command);

        // Funzione per impostare specifici orari di accensione e spegnimento del dispositivo
        virtual void set(std::string start, std::string stop);

        // auto-start si azzera
        virtual void rm();

        // Mostra a schermo produzione/consumo energetico di un dispositivo specifico
        void show();

        // Ritorna il nome del dispostivo
        std::string get_name();

        // Ritorna il valore di consumo del dispositivo
        int get_consumption();

        // Ritorna lo stato di accensione del dispositivo
        bool get_is_on();

        // Ritorna il valore di auto_start
        Stime get_autoStart();

        // Ritorna il valore di total_consumption
        int get_total_consumption();

        // Aggiorna il valore di total_consumption in base a quanto ha consumato il dispositivo finora
        virtual void update_total_consumption(Stime t);

        // Resetta i consumi totali
        void reset_total_consumption();
};

#endif // DEVICE_H