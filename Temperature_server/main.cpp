#include <vsomeip/vsomeip.hpp>
#include "../include/temperature_interface_v001.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "../include/serialization_helpers.hpp"

class TemperatureServer {
public:
    TemperatureServer()
        : app_(vsomeip::runtime::get()->create_application("Sensor_server")),
          temperature_(25) {}

    void init() {
        app_->init();
        app_->register_state_handler([this] (vsomeip::state_type_e state) {
            if (state == vsomeip::state_type_e::ST_REGISTERED) {
                app_->offer_service(TEMPERATURE_SERVICE_ID, TEMPERATURE_INSTANCE_ID);
                app_->offer_event(TEMPERATURE_SERVICE_ID, TEMPERATURE_INSTANCE_ID,
                                  TEMPERATURE_EVENT_ID, {TEMPERATURE_EVENTGROUP_ID}, vsomeip::event_type_e::ET_EVENT);
                std::thread(&TemperatureServer::run, this).detach();
            }
        });
    }

    void start() {
        app_->start();
    }

private:
    void run() {
        while (true) {
            std::vector<vsomeip::byte_t> payload_data = serialization::serializeStruct(temperature_);

            auto payload = vsomeip::runtime::get()->create_payload();
            payload->set_data(payload_data);

            app_->notify(TEMPERATURE_SERVICE_ID, TEMPERATURE_INSTANCE_ID,
                         TEMPERATURE_EVENT_ID, payload);

            std::cout << "Server: Sent temperature = " << temperature_.value << "°C" <<" Interface version : " << temperature_.interface_version<< std::endl;

            temperature_.value = (temperature_.value + 1) % 40;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

    std::shared_ptr<vsomeip::application> app_;
    temperature_interface_v001::Temperature temperature_;
};

int main() {
    TemperatureServer server;
    server.init();
    server.start();
    return 0;
}
