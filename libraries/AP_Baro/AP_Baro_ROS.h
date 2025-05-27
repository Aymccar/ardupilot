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
    static AP_Baro_Backend *probe(AP_Baro &baro) {
        return NEW_NOTHROW AP_Baro_ROS(baro);
    }

private:
    uint8_t _instance;

    float pressure = 0;
    float temp = 0;

    BridgeNode* node;
    BridgeSubscriberArray* subscriber;
};

#endif
