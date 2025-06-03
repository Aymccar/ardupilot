/*
  ROS backend barometer. Used during board bringup. Selected using
  BARO line in hwdef.dat
 */
#pragma once

#include "AP_Baro_Backend.h"

#include <bridge_node.hpp> 

#if AP_BARO_ROS_ENABLED

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
