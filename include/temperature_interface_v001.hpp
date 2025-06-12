#ifndef TEMPERATURE_INTERFACE_HPP
#define TEMPERATURE_INTERFACE_HPP

#define TEMPERATURE_SERVICE_ID 0x1234
#define TEMPERATURE_INSTANCE_ID 0x5678
#define TEMPERATURE_EVENTGROUP_ID 0x4466
#define TEMPERATURE_EVENT_ID 0x3344


#include <string>

namespace temperature_interface_v001 {

struct Temperature {
    uint interface_version;
    int value;           // Temperature value
    // Constructor
    Temperature(int val)
        : value(val){}
};

} // namespace temperature_interface_v001


#endif // TEMPERATURE_INTERFACE_HPP

