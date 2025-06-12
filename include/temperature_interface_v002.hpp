#ifndef TEMPERATURE_INTERFACE_v002_HPP
#define TEMPERATURE_INTERFACE_v002_HPP

#define TEMPERATURE_SERVICE_ID 0x1234
#define TEMPERATURE_INSTANCE_ID 0x5678
#define TEMPERATURE_EVENTGROUP_ID 0x4466
#define TEMPERATURE_EVENT_ID 0x3344

#include <string>

namespace temperature_interface_v002 {

struct Temperature {
    double value;           // Temperature value
    std::string unit;       // Unit: "C", "F", or "K"

    // Constructor
    Temperature(double val, const std::string& u)
        : value(val), unit(u) {}
};

} // namespace temperature_interface_v002


#endif // TEMPERATURE_INTERFACE_HPP
