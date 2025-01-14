// Tutto il gruppo

#include "../include/system.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#define BOLD    "\033[1m"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

std::vector<Device*> devices;

System::System() {
    // Inizializziamo i dispositivi all'interno di System

    // Dispositivi M

    // Impianto Fotovoltaico / Manuale / +1500W
    M* pv = new M("Impianto fotovoltaico", 0, 1500);
    devices.push_back(pv);

    // Pompa di Calore / Manuale / -2000W
    M* hp = new M("Pompa di calore + termostato", 1, -2000);
    devices.push_back(hp);

    // Scaldabagno / Manuale / -1000W
    M* boiler = new M("Scaldabagno", 2, -1000);
    devices.push_back(boiler);

    // Frigorifero / Manuale / -400W
    M* fridge = new M("Frigorifero", 3, -400);
    devices.push_back(fridge);

    // Dispositivi CP

    // Lavatrice - CP / Ciclo: 1h 50m / -2000W
    CP* wm = new CP("Lavatrice", 4, -2000, {"01:50"});
    devices.push_back(wm);

    // Lavastoviglie / CP / Ciclo: 3h 15m / -1500W 
    CP* dw = new CP("Lavastoviglie", 5, -1500, {"03:15"});
    devices.push_back(dw);

    // Tapparelle Elettriche / CP / Ciclo: 1m / -300W
    CP* blinds = new CP("Tapparelle elettriche", 6, -300, {"00:01"});
    devices.push_back(blinds);

    // Forno a Microonde / CP / Ciclo: 2m / -800W
    CP* microwave = new CP("Forno a microonde", 7, -800, {"00:02"});
    devices.push_back(microwave);

    // Asciugatrice / CP / Ciclo: 1h / -500W
    CP* dryer = new CP("Asciugatrice", 8, -500, {"01:00"});
    devices.push_back(dryer);

    // Televisore / CP / Ciclo: 1h / -200W
    CP* tv = new CP("Televisore", 9, -200, {"01:00"});
    devices.push_back(tv);
}

Device* System::search_device(std::string device_name){
    Device* p = nullptr;
    for (int i = 0; i < devices.size(); i++){
        if (devices[i] -> get_name() == device_name){
            p = devices[i];
            break;
        }
    }
    return p;
}

void System::show_all(){
    Stime duration;
    // Variabile per la produzione energetica
    double XX = 0;
    // Variabile per il consumo energetico
    double YY = 0;
    Stime midnight = {"00:00"};
    
    for (int i = 0; i < devices.size(); i ++){
        duration = current_time - devices[i] -> get_autoStart();
        double total_device_consumption = 0;
        if (devices[i] -> get_is_on() == true && devices[i] -> get_autoStart() != midnight){
            total_device_consumption = devices[i] -> get_consumption() * (duration.get_hours() + ((double)duration.get_minutes()/60)) + devices[i] -> get_total_consumption();
        } else {
            total_device_consumption = devices[i] -> get_total_consumption();
        }
        
        if (devices[i] -> get_name() == "Impianto fotovoltaico"){
            XX = total_device_consumption;
            std::cout << "L'Impianto fotovoltaico " << "produce: " << GREEN << total_device_consumption << " Wh" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } else {
            std::cout << "Il dispositivo " << devices[i] -> get_name() << " ha consumato: " << RED << total_device_consumption << " Wh" << RESET << std::endl;
            YY += total_device_consumption;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    std::cout << "Attualmente il sistema ha prodotto " << GREEN << XX << " Wh" << RESET <<  " e consumato " << RED << YY << " Wh." << RESET << std::endl;
}

double System::set_time(std::string t){
    Stime time{t};
    // Vettore in cui mettiamo i dispositivi ordinati in ordine crescente di spegnimento
    std::vector<Device*> d_off;
    // Produzione elettrica dell'impianto fotovoltaico
    double pv_production = 0;
    // Non si può (ancora :O) tornare indietro nel tempo
    if (time < current_time){
        std::cout << RED << "Errore: non puoi tornare indietro nel tempo!" << RESET << std::endl;
        return pv_production;
    }

    // Facciamo un bool che ci controlla che ci sia almeno un dispositivo che è stato acceso
    // altrimenti si esce dalla funzione visto che non è stato fatto niente.
    // Sfruttiamo il for per copiare il vettore in modo da non doverne scrivere un altro
    bool spenti = true;
    for (int i = 0; i < devices.size(); i++){
        d_off.push_back(devices[i]);
        if (devices[i] -> get_is_on() == true) spenti = false;
    }

    if (spenti){
        std::cout << "Non è stato acceso nessun dispositivo finora" << std::endl;
        current_time = time;
        std::cout << "L'orario attuale è: [" << current_time << "]" << std::endl;
        return pv_production;
    } 
    
    devices_sorting_on();
    devices_sorting_off(d_off);

    // Ora dobbiamo scorrere in parallelo i due vettori e stampare in base all'orario di accensione o di spegnimento
    // a seconda di quale viene prima
    
    int a_counter = 0;
    int s_counter = 0;
    CP* cp_a = dynamic_cast<CP*>(devices[a_counter]);
    M* m_a = dynamic_cast<M*>(devices[a_counter]);
    CP* cp_s = dynamic_cast<CP*>(d_off[s_counter]);
    M* m_s = dynamic_cast<M*>(d_off[s_counter]);
    // Variabile evitare che vengano stampati dispositivi mai accesi
    Stime midnight{"00:00"};

    // Cerchiamo il primo elemento che si accende dopo l'orario attuale
    while (a_counter<devices.size() && ((devices[a_counter] -> get_autoStart()) < current_time)){
        a_counter++;
    }

    while (s_counter < d_off.size()){
        cp_s = dynamic_cast<CP*>(d_off[s_counter]);
        m_s = dynamic_cast<M*>(d_off[s_counter]);
        if (cp_s){
            if (cp_s -> get_autoStart() + cp_s -> get_duration() < current_time){
                s_counter++;
            } else {
                break;
            }
        }
        if (m_s){
            if (m_s -> get_stop() < current_time){
                s_counter++;
            } else {
                break;
            }
        }
    }

    // Caso in cui non abbiamo acceso nessun dispositivo dopo l'orario passato come parametro (time)
    if (a_counter == devices.size()){
        while (s_counter < d_off.size()){
            cp_s = dynamic_cast<CP*>(d_off[s_counter]);
            m_s = dynamic_cast<M*>(d_off[s_counter]);
            if (cp_s){
                if (cp_s -> get_autoStart() + cp_s -> get_duration() > time){
                    break;
                } else {
                    if (cp_s -> get_autoStart() != midnight){
                        current_time = cp_s -> get_autoStart() + cp_s -> get_duration();
                        cp_s -> update_total_consumption(current_time);
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << cp_s -> get_name() << " si è " << RED << "spento" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        cp_s -> set("off");
                    }
                    s_counter++;
                }
            }
            if (m_s){
                if (m_s -> get_stop() > time){
                    break;
                } else {
                    if (m_s -> get_autoStart() != midnight){
                        // Calcoliamo la produzione dell'impianto fotovoltaico
                        if (m_s -> get_name() == "Impianto fotovoltaico"){
                            Stime duration = m_s -> get_stop() - m_s -> get_autoStart();
                            pv_production = (duration.get_hours() + ((double)duration.get_minutes()/60)) * m_s -> get_consumption();
                        }
                        current_time = m_s -> get_stop();
                        m_s -> update_total_consumption(current_time);
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << m_s -> get_name() << " si è " << RED << "spento" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        m_s -> set("off");
                    }
                    s_counter++;
                }
            }
        }
    }

    // Caso in cui non abbiamo spento nessun dispositivo dopo l'orario passato come parametro (time)
    if (s_counter == d_off.size()){
        while (a_counter < devices.size()){
            cp_a = dynamic_cast<CP*>(devices[a_counter]);
            m_a = dynamic_cast<M*>(devices[a_counter]);
            if (cp_a){
                if (cp_a -> get_autoStart() > time){
                    break;
                } else {
                    if (cp_a -> get_autoStart() != midnight){
                        current_time = cp_a -> get_autoStart();
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << cp_a -> get_name() << " si è " << GREEN << "acceso" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
                    a_counter++;
                }
            }
            if (m_a){
                if (m_a -> get_autoStart() > time){
                    break;
                } else {
                    if (m_a -> get_autoStart() != midnight){
                        current_time = m_a -> get_autoStart();
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << m_a -> get_name() << " si è " << GREEN << "acceso" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        m_a -> set("off");
                    }
                    a_counter++;
                }
            }
        }
    }

    // Caso in cui non abbiamo finito di scorrere nessuno dei due vettori
    while (a_counter < devices.size() && s_counter < d_off.size()){
            // Confronto tra un CP acceso e un CP spento
            cp_a = dynamic_cast<CP*>(devices[a_counter]);
            m_a = dynamic_cast<M*>(devices[a_counter]);
            cp_s = dynamic_cast<CP*>(d_off[s_counter]);
            m_s = dynamic_cast<M*>(d_off[s_counter]);
            if (cp_a && cp_s){
                if (cp_a -> get_autoStart() < cp_s -> get_autoStart() + cp_s -> get_duration()){
                    // Nel caso in cui l'orario richiesto dall'utente è minore (ciò significa che è stato superato e non
                    // va mostrato quello che succede dopo)
                    if (cp_a -> get_autoStart() > time) break;
                    if (cp_a -> get_autoStart() != midnight){
                        current_time = cp_a -> get_autoStart();
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << cp_a -> get_name() << " si è " << GREEN << "acceso" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
                    a_counter++;
                } else {
                    // Nel caso in cui l'orario richiesto dall'utente è minore (ciò significa che è stato superato e non
                    // va mostrato quello che succede dopo)
                    if (cp_s -> get_autoStart() + cp_s -> get_duration() > time) break;
                    if (cp_s -> get_autoStart() != midnight){
                        current_time = cp_s -> get_autoStart() + cp_s -> get_duration();
                        cp_s -> update_total_consumption(current_time);
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << cp_s -> get_name() << " si è " << RED << "spento" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        cp_s -> set("off");
                    }
                    s_counter++;
                }
            }

            // Confronto tra un CP acceso e un M spento
            if (cp_a && m_s){
                if (cp_a -> get_autoStart() < m_s -> get_stop()){
                    if (cp_a -> get_autoStart() > time) break;
                    if (cp_a -> get_autoStart() != midnight){
                        current_time = cp_a -> get_autoStart();
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << cp_a -> get_name() << " si è " << GREEN << "acceso" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
                    a_counter++;
                } else {
                    if (m_s -> get_stop() > time) break;
                    if (m_s -> get_autoStart() != midnight){
                        // Calcoliamo la produzione dell'impianto fotovoltaico
                        if (m_s -> get_name() == "Impianto fotovoltaico"){
                            Stime duration = m_s -> get_stop() - m_s -> get_autoStart();
                            pv_production = (duration.get_hours() + ((double)duration.get_minutes()/60)) * m_s -> get_consumption();
                        }
                        current_time = m_s -> get_stop();
                        m_s -> update_total_consumption(current_time);
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << m_s -> get_name() << " si è " << RED << "spento" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        m_s -> set("off");
                    }
                    s_counter++;
                }
            }

            // Confronto tra un M acceso e un M spento
            if (m_a && m_s){
                if (m_a -> get_autoStart() < m_s -> get_stop()){
                    if (m_a -> get_autoStart() > time) break;
                    if (m_a -> get_autoStart() != midnight){
                        current_time = m_a -> get_autoStart();
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << m_a -> get_name() << " si è " << GREEN << "acceso" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
                    a_counter++;
                } else {
                    if (m_s -> get_stop() > time) break;
                    if (m_s -> get_autoStart() != midnight){
                        // Calcoliamo la produzione dell'impianto fotovoltaico
                        if (m_s -> get_name() == "Impianto fotovoltaico"){
                            Stime duration = m_s -> get_stop() - m_s -> get_autoStart();
                            pv_production = (duration.get_hours() + ((double)duration.get_minutes()/60)) * m_s -> get_consumption();
                        }
                        current_time = m_s -> get_stop();
                        m_s -> update_total_consumption(current_time);
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << m_s -> get_name() << " si è " << RED << "spento" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        m_s -> set("off");
                    }
                    s_counter++;
                }
            }

            // Confronto tra un M acceso e un CP spento
            if (m_a && cp_s){
                if (m_a -> get_autoStart() < cp_s -> get_autoStart() + cp_s -> get_duration()){
                    if (m_a -> get_autoStart() > time) break;
                    if (m_a -> get_autoStart() != midnight){
                        current_time = m_a -> get_autoStart();
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << m_a -> get_name() << " si è " << GREEN << "acceso" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
                    a_counter++;
                } else {
                    if (cp_s -> get_autoStart() + cp_s -> get_duration() > time) break;
                    if (cp_s -> get_autoStart() != midnight){
                        current_time = cp_s -> get_autoStart() + cp_s -> get_duration();
                        cp_s -> update_total_consumption(current_time);
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << cp_s -> get_name() << " si è " << RED << "spento" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        cp_s -> set("off");
                    }
                    s_counter++;
                }
            }

    }

    // Abbiamo finito di scorrere gli spegnimenti quindi s_counter = d_off.size()
    // Scorriamo tutto il vettore di accensione
    if(s_counter == d_off.size()){
       while (a_counter < devices.size() && devices[a_counter] -> get_autoStart() < time){
        if (devices[a_counter] -> get_autoStart() != midnight){
            current_time = devices[a_counter] -> get_autoStart();
            std::cout << "[" << current_time << "] ";
            std::cout << "Il dispositivo " << devices[a_counter] -> get_name() << " si è " << GREEN << "acceso" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        a_counter++;
      } 
    }

    // Abbiamno finito di scorrere le accensioni, quindi a_counter = devices.size()
    // Scorriamo tutto il vettore di spegnimento
    if (a_counter == devices.size()){
        while (s_counter < d_off.size()){
            cp_s = dynamic_cast<CP*>(d_off[s_counter]);
            m_s = dynamic_cast<M*>(d_off[s_counter]);
            if (cp_s){
                if (cp_s -> get_autoStart() + cp_s -> get_duration() > time){
                    break;
                } else {
                    if (cp_s -> get_autoStart() != midnight){
                        current_time = cp_s -> get_autoStart() + cp_s -> get_duration();
                        cp_s -> update_total_consumption(current_time);
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << cp_s -> get_name() << " si è " << RED << "spento" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        cp_s -> set("off");
                    }
                    s_counter++;
                }
            }
            if (m_s){
                if (m_s -> get_stop() > time){
                    break;
                } else {
                    if (m_s -> get_autoStart() != midnight){
                        // Calcoliamo la produzione dell'impianto fotovoltaico
                        if (m_s -> get_name() == "Impianto fotovoltaico"){
                            Stime duration = m_s -> get_stop() - m_s -> get_autoStart();
                            pv_production = (duration.get_hours() + ((double)duration.get_minutes()/60)) * m_s -> get_consumption();
                        }
                        current_time = m_s -> get_stop();
                        m_s -> update_total_consumption(current_time);
                        std::cout << "[" << current_time << "] ";
                        std::cout << "Il dispositivo " << m_s -> get_name() << " si è " << RED << "spento" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        m_s -> set("off");
                    }
                    s_counter++;
                }
            }
        }
    }
    std::cout << "L'orario attuale è: [" << time << "]" << std::endl;
    current_time = time;
    return pv_production;
}

void System::reset_time(){
    current_time.set_time("00:00");
    for (int i = 0; i < devices.size(); i++){
        devices[i] -> reset_total_consumption();
        if (devices[i] -> get_is_on() == true){
            devices[i] -> set("off");
            // Creiamo un puntatore a M per poter azzerare anche stop
            M* m_ptr = dynamic_cast<M*>(devices[i]);
            if (m_ptr) m_ptr -> rm();
            std::cout << "[" << current_time << "] Rimosso il timer dal dispositivo " << devices[i] -> get_name() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    
    std::cout << "L'orario attuale è: [" << current_time << "]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Il sistema è stato riportato alle condizioni iniziali" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void System::reset_timers(){
    for (int i = 0; i < devices.size(); i++){
        if (devices[i] -> get_is_on() == true){
            devices[i] -> rm();
            std::cout << "[" << current_time << "] Il dispositivo " << devices[i] -> get_name() << " è " << GREEN << "acceso" << RESET;
            std::cout << " e il timer è stato azzerato a: [" << devices[i] -> get_autoStart() << "]" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }   
    }
}

void System::reset_all(){
    for (int i = 0; i < devices.size(); i++){
        devices[i] -> reset_total_consumption();
        // Creiamo due puntatori dei due diversi tipi di device allo stesso item del vettore
        M* m_ptr = dynamic_cast<M*>(devices[i]);
        CP* cp_ptr = dynamic_cast<CP*>(devices[i]);
        if (m_ptr){
            if (m_ptr -> get_is_on() == true){
                m_ptr -> set("off");
                std::cout << "[" << current_time << "] Il dispositivo " << m_ptr -> get_name() << " è stato " << RED << "spento" << RESET;
                std::cout << " e il timer è stato azzerato a: [" << m_ptr -> get_autoStart() << "]" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        } else {
            if (cp_ptr -> get_is_on() == true) {
                cp_ptr -> set("off");
                std::cout << "[" << current_time << "] Il dispositivo " << cp_ptr -> get_name() << " è stato " << RED << "spento" << RESET;
                std::cout << " e il timer è stato azzerato a: [" << cp_ptr -> get_autoStart() << "]" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
    }
    current_time.set_time("00:00");
    std::cout << "L'orario attuale è: [" << current_time << "]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void System::devices_sorting_on(){
    std::sort(devices.begin(), devices.end(), [](Device* a, Device* b){
        return a -> get_autoStart() < b -> get_autoStart();
    });
}

void System::devices_sorting_off(std::vector<Device*>& v){
    std::sort(v.begin(), v.end(), [this](Device* a, Device* b) {
        return compare_devices(a, b);
    });
}

bool System::compare_devices(Device* a, Device* b) {
    CP* cp_a = dynamic_cast<CP*>(a);
    CP* cp_b = dynamic_cast<CP*>(b);
    M* m_a = dynamic_cast<M*>(a);
    M* m_b = dynamic_cast<M*>(b);
    
    Stime time_a;
    if (cp_a) time_a = cp_a->get_autoStart() + cp_a->get_duration();
    if (m_a) time_a = m_a->get_stop();

    Stime time_b;
    if (cp_b) time_b = cp_b->get_autoStart() + cp_b->get_duration();
    if (m_b) time_b = m_b->get_stop();

    return time_a < time_b;
}

int System::get_system_limit(){
    return system_limit;
}