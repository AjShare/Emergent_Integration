#include <vsomeip/vsomeip.hpp>
#include "../include/temperature_interface.hpp"
#include <iostream>

class TemperatureClient {
public:
    TemperatureClient()
        : app_(vsomeip::runtime::get()->create_application("Display_Client")) {}

    void init() {
        app_->init();

        app_->register_state_handler([this] (vsomeip::state_type_e state){
            if (state == vsomeip::state_type_e::ST_REGISTERED) {
                app_->request_service(TEMPERATURE_SERVICE_ID, TEMPERATURE_INSTANCE_ID);
                app_->request_event(TEMPERATURE_SERVICE_ID, TEMPERATURE_INSTANCE_ID,
                                    TEMPERATURE_EVENT_ID, {TEMPERATURE_EVENTGROUP_ID}, vsomeip::event_type_e::ET_EVENT);
                app_->subscribe(TEMPERATURE_SERVICE_ID, TEMPERATURE_INSTANCE_ID,
                                TEMPERATURE_EVENTGROUP_ID);
            }
        });

        app_->register_message_handler(TEMPERATURE_SERVICE_ID, TEMPERATURE_INSTANCE_ID,
                                       TEMPERATURE_EVENT_ID,
                                       [this](std::shared_ptr<vsomeip::message> msg) {
                                           auto payload = msg->get_payload();
                                           auto data = payload->get_data();
                                           auto length = payload->get_length();
                                           if (length > 0)  {
                                               int temperature = static_cast<int>(data[0]);
                                               std::cout << "Client: Received temperature = "
                                                         << temperature << "°C" << std::endl;
                                           }
                                       });
    }

    void start() {
        app_->start();
    }

private:
    std::shared_ptr<vsomeip::application> app_;
};

int main() {
    TemperatureClient client;
    client.init();
    client.start();
    return 0;
}
