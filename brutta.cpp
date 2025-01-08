/*
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


// Creiamo due puntatori dei due diversi tipi di device allpo stesso item del vettore
        M* m_ptr = dynamic_cast<M*>(&devices[i]);
        CP* cp_ptr = dynamic_cast<CP*>(&devices[i]);
*/