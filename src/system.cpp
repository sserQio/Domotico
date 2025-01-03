#include "../include/system.h"

//DEFINIRE IL VECTOR DI M
M* search_m_device(std::string device_name){
    M *p = nullptr;
    for(int i=0; i<4; i++){
        if(m_devices[i].getName() == device_name){
            p = &m_devices[i];
            break;
        }
    }
    
    return p ;
}

CP* search_cp_device(std::string device_name){
    CP *p = nullptr;
    for(int i=0; i<4; i++){
        if(cp_devices[i].getName() == device_name){
            p = &cp_devices[i];
            break;
        }
    }
    
    return p ;
}

