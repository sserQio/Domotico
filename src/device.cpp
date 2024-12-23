#include "../include/device.h"

Device::Device(std::string n, int i, double c):
    name {n},
    id {i},
    consumption {c},
    autoStart {"00:00"},
    is_on {false}
{}


