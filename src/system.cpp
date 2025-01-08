#include "../include/system.h"

std::vector<M> m_devices;
std::vector<CP> cp_devices;

std::vector<Device> devices;

Device* search_device(std::string device_name){
    Device* p = nullptr;
    for (int i = 0; i < devices.size(); i++){
        if (devices[i].get_name() == device_name){
            p = &devices[i];
            break;
        }
    }
    return p;
}

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

void System::show(){
    Time duration;
    std::cout << "[ ";
    current_time.print_time();  // Utilizziamo le nostre funzioni :D
    std::cout << " ]" << std::endl;
    int XX = 0;
    int YY = 0;
    
    for (int i = 0; i < devices.size(); i ++){
        duration = current_time - devices[i].get_autoStart();
        double total_device_consumption = devices[i].get_consumption() * (duration.get_hours() + ((double)duration.get_minutes()/60));
        if (devices[i].get_name() == "Impianto Fotovoltaico"){
            XX = devices[i].get_consumption();
            std::cout << "L'Impianto Fotovoltaico produce: " << total_device_consumption;
        } else {
            std::cout << "Il dispositivo" << devices[i].get_name() << " ha consumato: " << total_device_consumption << std::endl;
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

    std::vector<Device> d_off;

    for (int i = 0; i < devices.size(); i++){
        d_off.push_back(devices[i]);
    }
    
    devices_sorting_on();
    devices_sorting_off(d_off);

    // dobbiamo scorrere in parallelo i due vettori e stampare in base all'orario di accensione o di spegnimento
    // a seconda di quale viene prima

    // ricordare di cambiare
    // current time = time 
}

void System::reset_time(){
    current_time.set_time("00:00");
    for (int i = 0; i < devices.size(); i++){
        if (devices[i].get_is_on() == true) devices[i].rm();
    }
}

void System::reset_all(){
    current_time.set_time("00:00");
    for (int i = 0; i < devices.size(); i++){
        // Creiamo due puntatori dei due diversi tipi di device allpo stesso item del vettore
        M* m_ptr = dynamic_cast<M*>(&devices[i]);
        CP* cp_ptr = dynamic_cast<CP*>(&devices[i]);
        if (m_ptr){
            if (m_ptr -> get_is_on() == true) m_ptr -> set("off");
        } else {
            if (cp_ptr -> get_is_on() == true) cp_ptr -> set("off");
        }
    }
}

void System::devices_sorting_on(){
    std::sort(devices.begin(), devices.end(), [](Device a, Device b){
        return a.get_autoStart() < b.get_autoStart();
    });
}

void System::devices_sorting_off(std::vector<Device>& v){
    std::sort(v.begin(), v.end(), compare_devices);
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
}