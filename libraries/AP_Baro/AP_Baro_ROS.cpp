#include "AP_Baro_ROS.h"

#include <bridge_node.hpp> 

#if AP_BARO_ROS_ENABLED
AP_Baro_ROS::AP_Baro_ROS(AP_Baro &baro) :
    AP_Baro_Backend(baro)
{
    _instance = _frontend.register_sensor();
    _frontend.set_type(0, AP_Baro::BARO_TYPE_WATER);

    node = new BridgeNode("Baro");
    subscriber = node->create_subscriber_array("/Baro_P_T", 5, 
            [this](array_msg_t data){
                this->pressure = data.data[0]; //Not zero
                this->temp = 23; //placeholder
            });
}

// Read the sensor
void AP_Baro_ROS::update(void)
{
    node->spin_some();

    _copy_to_frontend(0, pressure, temp);
}

#endif  
