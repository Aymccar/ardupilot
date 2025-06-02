#include "AP_Compass_ROS.h"

#include <bridge_node.hpp>

#if AP_COMPASS_ROS_ENABLED

const extern AP_HAL::HAL& hal;

AP_Compass_Backend* AP_Compass_ROS::probe(enum Rotation rotation){
    AP_Compass_ROS* sensor = NEW_NOTHROW AP_Compass_ROS(rotation);
    if (sensor->_init()){
        return sensor;
    } else {
        return nullptr;
    }
}

AP_Compass_ROS::AP_Compass_ROS(enum Rotation rotation):
    _rotation(rotation){}

bool AP_Compass_ROS::_init(){

    auto _dev_id = AP_HAL::Device::make_bus_id(AP_HAL::Device::BUS_TYPE_SITL, 1, 0, 0);

    register_compass(1, _compass_instance);

    set_dev_id(_compass_instance, _dev_id);
    set_rotation(_compass_instance, _rotation);

    node = new BridgeNode("Compass");
    subscriber = node->create_subscriber_array("/Compass", 5, 
            [this](array_msg_t msg){});
    
    return true;
}

void AP_Compass_ROS::_update(){
    node->spin_some();
    array_msg_t msg = subscriber->get();

    Vector3 field = {(float)msg.data[0], (float)msg.data[1], (float)msg.data[2]};
    accumulate_sample(field, _compass_instance);
}

void AP_Compass_ROS::read(){
    _update();
    drain_accumulated_samples(_compass_instance);
}

#endif
