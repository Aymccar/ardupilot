#include "AP_Dev_Backend.h"

bool Dev_Backend::init() {
    const auto& serial_manager = AP::serialmanager();
    AP_HAL::UARTDriver *driv = serial_manager.find_serial(AP_SerialManager::SerialProtocol_Dev, 0);
    _driv = driv;
    if (!_driv) {
        gcs().send_text(MAV_SEVERITY_CRITICAL, "No UART device for Dev");
        return false;
    }
}

void Dev_Backend::start() {
    hal.scheduler->register_timer_process(FUNCTOR_BIND_MEMBER(&AP_Dev_Backend::update, void));
}

void Dev_Backend::do_something(){};

int Dev_Backend::update() {
    const unsigned char  
    //_driv->read(...); //TODO check in AP_HAL and AP_InertialSensor/AP_InertialSensor_ORIENTUS.*
    do_something();
}
