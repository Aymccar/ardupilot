#pragma once
#include "AP_HAL_Linux.h"

#include <bridge_node.hpp>

namespace Linux {

class RCOutput_ROS : public AP_HAL::RCOutput {
public :
    RCOutput_ROS();
    ~RCOutput_ROS();

    void init() override;

    void set_freq(uint32_t chmask, uint16_t freq_hz) override;
    uint16_t get_freq(uint8_t ch) override;

    void enable_ch(uint8_t ch) override;
    void disable_ch(uint8_t ch) override;

    void write(uint8_t chan, uint16_t period_us) override;
    void cork() override; 
    void push() override;

    uint16_t read(uint8_t chan) override;
    void read(uint16_t* period_us, uint8_t len) override;

    bool supports_gpio() override { return true; };
    void write_gpio(uint8_t ch, bool active) override;

private:
        uint16_t _freq;
        bool _corking;
        uint16_t* _pulse_buffer;

        BridgeNode* node;
        BridgePublisherArray* publisher;
};
}
