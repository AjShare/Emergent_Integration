#include <vsomeip/vsomeip.hpp>
#include "../include/humidity_interface_v001.hpp"
#include <iostream>
#include <thread>
#include <chrono>

class SunlightServer {
public:
    SunlightServer()
        : app_(vsomeip::runtime::get()->create_application("Sunlight_server")),
          humidity_(25) {}

    void init() {
        app_->init();
        app_->register_state_handler([this] (vsomeip::state_type_e state) {
            if (state == vsomeip::state_type_e::ST_REGISTERED) {
                app_->offer_service(HUMIDITY_SERVICE_ID, HUMIDITY_INSTANCE_ID);
                app_->offer_event(HUMIDITY_SERVICE_ID, HUMIDITY_INSTANCE_ID,
                                  HUMIDITY_EVENT_ID, {HUMIDITY_EVENTGROUP_ID}, vsomeip::event_type_e::ET_EVENT);
                std::thread(&SunlightServer::run, this).detach();
            }
        });
    }

    void start() {
        app_->start();
    }

private:
    void run() {
        while (true) {
            std::vector<vsomeip::byte_t> payload_data = {
                static_cast<vsomeip::byte_t>(humidity_)
            };

            auto payload = vsomeip::runtime::get()->create_payload();
            payload->set_data(payload_data);

            app_->notify(HUMIDITY_SERVICE_ID, HUMIDITY_INSTANCE_ID,
                         HUMIDITY_EVENT_ID, payload);

            std::cout << "Server: Sent humidity = " << humidity_ << std::endl;

            humidity_ = (humidity_ + 1) % 40;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

    std::shared_ptr<vsomeip::application> app_;
    int humidity_;
};

int main() {
    SunlightServer server;
    server.init();
    server.start();
    return 0;
}
