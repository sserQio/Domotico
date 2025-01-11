#include "../include/system.h"

//std::vector<M> m_devices;
//std::vector<CP> cp_devices;

std::vector<Device*> devices;

System::System() {
    // Inizializziamo i dispositivi all'interno di System

    // Dispositivi M

    // Impianto Fotovoltaico / Manuale / +1500W
    M* pv = new M("Impianto Fotovoltaico", 0, 1500);
    devices.push_back(pv);

    // Pompa di Calore / Manuale / -2000W
    M* hp = new M("Pompa di Calore", 1, -2000);
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
    CP* blinds = new CP("Tapparelle", 6, -300, {"00:01"});
    devices.push_back(blinds);

    // Forno a Microonde / CP / Ciclo: 2m / -800W
    CP* microwave = new CP("Microonde", 7, -800, {"00:02"});
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

/*
M* search_m_device(std::string device_name){
    M *p = nullptr;
    for (int i = 0; i < 4; i++){ // DA CAMBIARE IL VALORE 4
        if (m_devices[i].get_name() == device_name){
            p = &m_devices[i];
            break;
        }
    }
    return p ;
}
CP* search_cp_device(std::string device_name){
    CP *p = nullptr;
    for (int i = 0; i < 4; i++){ // DA CAMBIARE IL VALORE 4
        if (cp_devices[i].get_name() == device_name){
            p = &cp_devices[i];
            break;
        }
    }
    return p ;
}
*/

void System::show(){
    Stime duration;
    std::cout << "[ ";
    current_time.print_time();  // Utilizziamo le nostre funzioni :D
    std::cout << " ]" << std::endl;
    int XX = 0;
    int YY = 0;
    
    for (int i = 0; i < devices.size(); i ++){
        duration = current_time - devices[i] -> get_autoStart();
        double total_device_consumption = devices[i] -> get_consumption() * (duration.get_hours() + ((double)duration.get_minutes()/60));
        if (devices[i] -> get_name() == "Impianto Fotovoltaico"){
            XX = devices[i] -> get_consumption();
            std::cout << "L'Impianto Fotovoltaico produce: " << total_device_consumption;
        } else {
            std::cout << "Il dispositivo" << devices[i] -> get_name() << " ha consumato: " << total_device_consumption << std::endl;
            YY += total_device_consumption;
        }
    }
    std::cout << "Attualmente il sistema ha prodotto " << XX << " kWh e consumato " << YY << " kWh." << std::endl;
}

void System::set_time(std::string time){
    std::cout << "Salto all'ora scelta: " + time << std::endl;
    std::cout << "[ ";
    current_time.print_time();
    std::cout << " ]" << std::endl;

    std::vector<Device*> d_off;

    for (int i = 0; i < devices.size(); i++){
        d_off.push_back(devices[i]);
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

    // Cerchiamo il prmio elemento che si accende dopo l'orario attuale
    while (a_counter<devices.size() && devices[a_counter] -> get_autoStart() < current_time){
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
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << cp_s -> get_name() << " si è spento" << std::endl;
                    s_counter++;
                }
            }

            if (m_s){
                if (m_s -> get_stop() > time){
                    break;
                } else {
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << m_s -> get_name() << " si è spento" << std::endl;
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
                if (cp_a -> get_autoStart() + cp_a -> get_duration() > time){
                    break;
                } else {
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << cp_a -> get_name() << " si è spento" << std::endl;
                    a_counter++;
                }
            }

            if (m_a){
                if (m_a -> get_stop() > time){
                    break;
                } else {
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << m_a -> get_name() << " si è spento" << std::endl;
                    a_counter++;
                }
            }
        }
    }

    // Caso in cui non abbiamo finito di scorrere nessuno dei due vettori
    while (a_counter < devices.size() && s_counter < d_off.size()){
            // Confronto tra un CP acceso e un CP spento
            if (cp_a && cp_s){
                
                if (cp_a -> get_autoStart() < cp_s -> get_autoStart() + cp_s -> get_duration()){
                    // Nel caso in cui l'orario richiesto dall'utente è minore (ciò significa che è stato superato e non
                    // va mostrato quello che succede dopo)
                    if (cp_a -> get_autoStart() > time) break;

                    current_time = cp_a -> get_autoStart();
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << cp_a -> get_name() << " si è acceso" << std::endl;
                    a_counter++;
                } else {
                    // Nel caso in cui l'orario richiesto dall'utente è minore (ciò significa che è stato superato e non
                    // va mostrato quello che succede dopo)
                    if (cp_s -> get_autoStart() + cp_s -> get_duration() > time) break;

                    current_time = cp_s -> get_autoStart() + cp_s -> get_duration();
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << cp_s -> get_name() << " si è spento" << std::endl;
                    s_counter++;
                }
            }

            // Confronto tra un CP acceso e un M spento
            if (cp_a && m_s){
                if (cp_a -> get_autoStart() < m_s -> get_stop()){

                    if (cp_a -> get_autoStart() > time) break;

                    current_time = cp_a -> get_autoStart();
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << cp_a -> get_name() << " si è acceso" << std::endl;
                    a_counter++;
                } else {

                    if (m_s -> get_stop() > time) break;

                    current_time = m_s -> get_stop();
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << m_s -> get_name() << " si è spento" << std::endl;
                    s_counter++;
                }
            }

            // Confronto tra un M acceso e un M spento
            if (m_a && m_s){
                if (m_a -> get_autoStart() < m_s -> get_stop()){

                    if (m_a -> get_autoStart() > time) break;

                    current_time = m_a -> get_autoStart();
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << m_a -> get_name() << " si è acceso" << std::endl;
                    a_counter++;
                } else {

                    if (m_s -> get_stop() > time) break;

                    current_time = m_s -> get_stop();
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << m_s -> get_name() << " si è spento" << std::endl;
                    s_counter++;
                }
            }

            // Confronto tra un M acceso e un CP spento
            if (m_a && cp_s){
                if (m_a -> get_autoStart() < cp_s -> get_autoStart() + cp_s -> get_duration()){

                    if (m_a -> get_autoStart() > time) break;

                    current_time = m_a -> get_autoStart();
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << m_a -> get_name() << " si è acceso" << std::endl;
                    a_counter++;
                } else {

                    if (cp_s -> get_autoStart() + cp_s -> get_duration() > time) break;

                    current_time = cp_s -> get_autoStart() + cp_s -> get_duration();
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << cp_s -> get_name() << " si è spento" << std::endl;
                    s_counter++;
                }
            }

    }

    // Abbiamo finito di scorrere gli spegniemnti quindi s_counter = d_off.size()
    // Scorriamo tutto il vettore di accensione
    if(s_counter == d_off.size()){
       while (a_counter < devices.size() && devices[a_counter] -> get_autoStart() < time){
        current_time = devices[a_counter] -> get_autoStart();
        std::cout << "[ ";
        current_time.print_time();
        std::cout << " ]";
        std::cout << "Il dispositivo " << devices[a_counter] -> get_name() << " si è acceso" << std::endl;
        a_counter++;
      } 
    }

    // Abbiamno finito di scorrere le accensioni, quindi a_counter = devices.size()
    // Scorriamo tutto ilo vettore di spegnimento
    if (a_counter == devices.size()){
        while (s_counter < d_off.size()){
            cp_s = dynamic_cast<CP*>(d_off[s_counter]);
            m_s = dynamic_cast<M*>(d_off[s_counter]);
            if (cp_s){
                if (cp_s -> get_autoStart() + cp_s -> get_duration() > time){
                    break;
                } else {
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << cp_s -> get_name() << " si è spento" << std::endl;
                    s_counter++;
                }
            }
            if (m_s){
                if (m_s -> get_stop() > time){
                    break;
                } else {
                    std::cout << "[ ";
                    current_time.print_time();
                    std::cout << " ]";
                    std::cout << "Il dispositivo " << m_s -> get_name() << " si è spento" << std::endl;
                    s_counter++;
                }
            }
        }
    }
    
    current_time = time;
}

void System::reset_time(){
    current_time.set_time("00:00");
    for (int i = 0; i < devices.size(); i++){
        if (devices[i] -> get_is_on() == true) devices[i] -> rm();
    }
}

void System::reset_all(){
    current_time.set_time("00:00");
    for (int i = 0; i < devices.size(); i++){
        // Creiamo due puntatori dei due diversi tipi di device allpo stesso item del vettore
        M* m_ptr = dynamic_cast<M*>(devices[i]);
        CP* cp_ptr = dynamic_cast<CP*>(devices[i]);
        if (m_ptr){
            if (m_ptr -> get_is_on() == true) m_ptr -> set("off");
        } else {
            if (cp_ptr -> get_is_on() == true) cp_ptr -> set("off");
        }
    }
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

bool System::compare_devices(Device* a, Device* b){
    CP* cp_a = dynamic_cast<CP*>(a);
    CP* cp_b = dynamic_cast<CP*>(b);
    M* m_a = dynamic_cast<M*>(a);
    M* m_b = dynamic_cast<M*>(b);

    if (cp_a && cp_b){
        return (cp_a -> get_autoStart() + cp_a -> get_duration()) < (cp_b -> get_autoStart() + cp_b -> get_duration());
    }

    if (m_a && m_b){
        return m_a -> get_stop() < m_b -> get_stop();
    }

    if (m_a && cp_b){
        return m_a -> get_stop() < (cp_b -> get_autoStart() + cp_b -> get_duration());
    }

    if (m_b && cp_a){
        return m_b -> get_stop() < (cp_a -> get_autoStart() + cp_a -> get_duration());
    }

    return false;
}