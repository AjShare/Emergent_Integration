#ifndef HUMIDITY_INTERFACE_v001_HPP
#define HUMIDITY_INTERFACE_v001_HPP

#define SUNLIGHT_SERVICE_ID 0x4567
#define SUNLIGHT_INSTANCE_ID 0x8989
#define SUNLIGHT_EVENTGROUP_ID 0x5566
#define SUNLIGHT_EVENT_ID 0x5544

#include <string>

namespace humidity_interface_v001 {

struct Humidity {
    int value;           // Humidity value
    // Constructor
    Humidity(int val)
        : value(val){}
};

} // namespace humidity_interface_v001


#endif // HUMIDITY_INTERFACE_HPP
