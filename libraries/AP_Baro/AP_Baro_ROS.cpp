#include "AP_Baro_ROS.h"

#if AP_BARO_ROS_ENABLED

#include <bridge_server.hpp> 
#include <bridge_node.hpp> 

#include <AP_HAL/AP_HAL.h>

AP_Baro_ROS::AP_Baro_ROS(AP_Baro &baro) :
    AP_Baro_Backend(baro)
{
    _instance = _frontend.register_sensor();
    set_bus_id(_instance, AP_HAL::Device::make_bus_id(AP_HAL::Device::BUS_TYPE_SITL, 2, 0, 0));
    _frontend.set_type(_instance, AP_Baro::BARO_TYPE_WATER);
    init();
}

// Read the sensor
void AP_Baro_ROS::update(void)
{
    node->spin_some();

    _copy_to_frontend(_instance, pressure, temp);
}

void AP_Baro_ROS::init(){
    node = new BridgeNode("Baro", "Ardupilot");
    subscriber = node->create_subscriber_array("/Sea/Baro", 5, 
            [this](array_float_msg_t data){
                this->pressure = data.data[0]; 
                this->temp = 23; //placeholder
            });
    BridgeServer::init();
}

AP_Baro_Backend *AP_Baro_ROS::probe(AP_Baro &baro) {
    return NEW_NOTHROW AP_Baro_ROS(baro);
}

#endif  
