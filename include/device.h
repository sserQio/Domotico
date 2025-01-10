#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>
#include <vector>
#include "../include/stime.h"
// #include "../include/system.h"

class Device{
    private:
        // Nome del dispositivo
        std::string name;

        // ID numerico unico del dispositivo
        int id;

        // Consumo del dispositivo
        int consumption;

        // Varibile che definisce l'accensione o meno di un dispositivo
        bool is_on;

    protected:
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

        // Rimuove il timer di tutti i dispositivi. I dispositivi rimangono nello stato attuale
        // virtual void reset_timer() = 0;

        // Disabilita il costruttore di copia
        // Device(const Device&) = delete;

        // Disabilita l'operatore di assegnamento
        // Device& operator=(const Device&) = delete;

        // FUNZIONE PROVVISORIA
        // Stampa tutte le variabili di un oggetto
        void print();

        // Ritorna il nome del dispostivo
        std::string get_name();

        // Ritorna il valore di consumo del dispositivo
        int get_consumption();

        // Ritorna lo stato di accensione del dispositivo
        bool get_is_on();

        // Ritorna il valore di auto_start
        Stime get_autoStart();
};

#endif // DEVICE_H