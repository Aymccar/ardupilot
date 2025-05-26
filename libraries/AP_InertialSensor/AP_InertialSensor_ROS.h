#pragma once
#include "AP_InertialSensor.h"
#include "AP_InertialSensor_Backend.h"

#include <vector>

#include <bridge_node.hpp>

class AP_InertialSensor_ROS : public AP_InertialSensor_Backend {
public:
     
    static AP_InertialSensor_Backend* probe(AP_InertialSensor &imu, enum Rotation rotation);

    bool update() override;
    void start() override;

private:
    AP_InertialSensor_ROS(AP_InertialSensor &imu, enum Rotation rotation);
    void get_from_topic();

    BridgeNode* node;
    BridgeSubscriberIMU* subscriber; 

    std::vector<int> data;

    static uint8_t bus_id;
};

