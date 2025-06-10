#pragma once
#include "AP_Compass_Backend.h"

#if AP_COMPASS_ROS_ENABLED

#include <bridge_node.hpp>
#include <AP_HAL/AP_HAL.h>

class AP_Compass_ROS : public AP_Compass_Backend {
public:
    static AP_Compass_Backend* probe(enum Rotation rotation);
    void read() override;

    static constexpr const char *name = "ROS_Compass";

private:
    AP_Compass_ROS(enum Rotation rotation);

    void _update();
    bool _init();
    
    Rotation _rotation;
    uint8_t _compass_instance;

    BridgeNode* node;
    BridgeSubscriberArrayFloat* subscriber;

};
#endif
