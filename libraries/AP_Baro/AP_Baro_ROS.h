#pragma once

#include "AP_Baro_Backend.h"

#if AP_BARO_ROS_ENABLED

#include <bridge_node.hpp> 

class AP_Baro_ROS : public AP_Baro_Backend
{
public:
    AP_Baro_ROS(AP_Baro &baro);
    void update(void) override;
    static AP_Baro_Backend *probe(AP_Baro &baro);

private:

    void init();

    uint8_t _instance;
    AP_HAL::OwnPtr<AP_HAL::Device> _dev;

    static uint8_t bus_id;

    float pressure = 0;
    float temp = 0;

    BridgeNode* node;
    BridgeSubscriberArrayFloat* subscriber;
};

#endif
