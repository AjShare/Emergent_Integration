#ifndef TEMPERATURE_INTERFACE_v002_HPP
#define TEMPERATURE_INTERFACE_v002_HPP

#define TEMPERATURE_SERVICE_ID 0x1234
#define TEMPERATURE_INSTANCE_ID 0x5678
#define TEMPERATURE_EVENTGROUP_ID 0x4466
#define TEMPERATURE_EVENT_ID 0x3344

#include <string>

namespace temperature_interface_v002 {

struct Temperature {
    uint interface_version;
    double value;           // Temperature value
    int timestamp;       // Unit: "C", "F", or "K"

    // Constructor
    Temperature(int val = 0) : interface_version(1), value(val),timestamp(0) {}
};

} // namespace temperature_interface_v002

#endif // TEMPERATURE_INTERFACE_HPP
