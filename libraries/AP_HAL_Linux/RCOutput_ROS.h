#pragma once
#include "AP_HAL_Linux.h"

#include <bridge_node.hpp>
#include <bridge_publisher_string.hpp>

namespace Linux {

class RCOutput_ROS : public AP_HAL::RCOutput {
public :
    RCOutput_ROS();
    ~RCOutput_ROS();

    void init() override; //OK

    void set_freq(uint32_t chmask, uint16_t freq_hz) override; //OK
    uint16_t get_freq(uint8_t ch) override; //OK

    void enable_ch(uint8_t ch) override; //OK
    void disable_ch(uint8_t ch) override; //OK

    void write(uint8_t chan, uint16_t period_us) override; //OK
    
    void cork() override; //OK

    void push() override;

    uint16_t read(uint8_t chan) override;
    void read(uint16_t* period_us, uint8_t len) override;

private:
        uint16_t _freq;
        bool _corking;
        uint16_t* _pulse_buffer;

        BridgeNode node;
        BridgePublisherString publisher;


};
}
