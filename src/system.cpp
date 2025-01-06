#include "../include/system.h"

std::vector<M> m_devices;
std::vector<CP> cp_devices;

// DEFINIRE IL VECTOR DI M
M* search_m_device(std::string device_name){
    M *p = nullptr;
    for(int i = 0; i < 4; i++){
        if(m_devices[i].get_name() == device_name){
            p = &m_devices[i];
            break;
        }
    }
    return p ;
}

CP* search_cp_device(std::string device_name){
    CP *p = nullptr;
    for(int i = 0; i < 4; i++){
        if(cp_devices[i].get_name() == device_name){
            p = &cp_devices[i];
            break;
        }
    }
    return p ;
}

void System::show(){
    Time duration;
    std::cout << "[ ";
    current_time.print_time();
    std::cout << " ]" << std::endl;
    // Utilizziamo le nostre funzioni :D
    int XX = 0;
    int YY = 0;
    for(int i = 0; i < 4; i++){
        duration = current_time - m_devices[i].get_autoStart();
        double total_device_consumption = m_devices[i].get_consumption() * (duration.get_hours() + ((double)duration.get_minutes()/60));
        if (m_devices[i].get_name() == "Impianto Fotovoltaico"){
            XX = m_devices[i].get_consumption();
            std::cout << "L'Impianto Fotovoltaico produce: " << total_device_consumption;
        } else {
            std::cout << "Il dispositivo" << m_devices[i].get_name() << " ha consumato: " << total_device_consumption << std::endl;
            YY += total_device_consumption;
        }
    }

    std::cout << "Attualmente il sistema ha prodotto " << XX << " kWh e consumato " << YY << " kWh." << std::endl;
}

void System::set_time(std::string time){
    std::cout << "Salto all'ora scelta: " + time << std::endl;
}

void System::reset_time(){
    current_time.set_time("00:00");
    for (int i = 0; i < m_devices.size(); i++){
        if (m_devices[i].get_is_on() == true) m_devices[i].rm();
        if (cp_devices[i].get_is_on() == true) cp_devices[i].rm();
    }
}

void System::reset_all(){
    current_time.set_time("00:00");
    for (int i = 0; i < m_devices.size(); i++){
        if (m_devices[i].get_is_on() == true) m_devices[i].set("off");
        if (cp_devices[i].get_is_on() == true) cp_devices[i].set("off");
    }
}