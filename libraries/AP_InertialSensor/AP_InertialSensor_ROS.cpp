#include "AP_InertialSensor_ROS.h"
#include <AP_HAL/AP_HAL.h>

#include <vector>

#include <bridge_node.hpp>

const extern AP_HAL::HAL& hal;

uint8_t AP_InertialSensor_ROS::bus_id = 0;

AP_InertialSensor_ROS::AP_InertialSensor_ROS(AP_InertialSensor &imu, enum Rotation rotation):
    AP_InertialSensor_Backend(imu)
{
    node = new BridgeNode("IMU");

    subscriber = node->create_subscriber_IMU("/bluerov/sensors/IMU", 5,
            [this](user_msg_t msg){}); 
}

void AP_InertialSensor_ROS::get_from_topic(){

    node->spin_some();
    user_msg_t msg = subscriber->get();
   
    auto accel = Vector3f(msg.accel_x, msg.accel_y, msg.accel_z);
    _notify_new_accel_sensor_rate_sample(accel_instance, accel);
    _rotate_and_correct_accel(accel_instance, accel);
    _notify_new_accel_raw_sample(accel_instance, accel, AP_HAL::micros64());

    _publish_temperature(accel_instance, 23);

    auto gyro = Vector3f(msg.gyro_x, msg.gyro_y, msg.gyro_z);
    _notify_new_gyro_sensor_rate_sample(gyro_instance, gyro);
    _rotate_and_correct_gyro(gyro_instance, gyro);
    _notify_new_gyro_raw_sample(gyro_instance, gyro, AP_HAL::micros64());
}

bool AP_InertialSensor_ROS::update(){

    update_accel(accel_instance);
    update_gyro(gyro_instance);

    return true;
}

void AP_InertialSensor_ROS::start()
{
    int gyro_sample_hz = 1000;
    int accel_sample_hz = 1000;

    if (!_imu.register_gyro(gyro_instance, gyro_sample_hz,
                            AP_HAL::Device::make_bus_id(AP_HAL::Device::BUS_TYPE_SITL, bus_id, 1, DEVTYPE_ROS)) ||
        !_imu.register_accel(accel_instance, accel_sample_hz,
                             AP_HAL::Device::make_bus_id(AP_HAL::Device::BUS_TYPE_SITL, bus_id, 2, DEVTYPE_ROS))) {
        return;
    }
    bus_id++;
    hal.scheduler->register_timer_process(FUNCTOR_BIND_MEMBER(&AP_InertialSensor_ROS::get_from_topic, void));
}

AP_InertialSensor_Backend* AP_InertialSensor_ROS::probe(AP_InertialSensor &imu, enum Rotation rotation){

    AP_InertialSensor_ROS* sensor = NEW_NOTHROW AP_InertialSensor_ROS(imu, rotation);
    return sensor;
}
