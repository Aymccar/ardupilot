#include "RCOutput_ROS.h"

#if CONFIG_HAL_BOARD_SUBTYPE == HAL_BOARD_SUBTYPE_LINUX_ROS

#include <bridge_server.hpp>
#include <bridge_node.hpp>

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <unistd.h>

#define PWM_CHAN_COUNT 16

using namespace Linux;

RCOutput_ROS::RCOutput_ROS():
    _pulse_buffer(NEW_NOTHROW uint16_t[PWM_CHAN_COUNT])
{
}
RCOutput_ROS::~RCOutput_ROS()
{
    //TODO should shutdown ros 
}

void RCOutput_ROS::init()
{
    set_freq(0, 50);

    //ROS things
    BridgeServer::init();
    node = new BridgeNode("Motor_Driver", "Ardupilot");
    publisher = node->create_publisher_array("/Sea/PWM", 10);
}

void RCOutput_ROS::set_freq(uint32_t chmask, uint16_t freq_hz)
{
    // Write the last pulse
    for (int i=0; i<PWM_CHAN_COUNT; i++){
        write(i, _pulse_buffer[i]);
    }

    _freq = freq_hz;
}

uint16_t RCOutput_ROS::get_freq(uint8_t ch){
    return _freq;
}

void RCOutput_ROS::enable_ch(uint8_t ch)
{
    //pass
}

void RCOutput_ROS::disable_ch(uint8_t ch)
{
    write(ch, 0);
}

void RCOutput_ROS::write_gpio(uint8_t ch, bool active){
    write(ch, active);
}


void RCOutput_ROS::write(uint8_t ch, uint16_t period_us)
{
    _pulse_buffer[ch] = period_us;

    if (!_corking) {
        _corking = true;
        push();
    }
}

void RCOutput_ROS::cork()
{
    _corking = true;
}

void RCOutput_ROS::push(){
    
    if (!_corking) {
        return;
    }

    _corking = false;
    if (publisher){
        publisher->publish(_pulse_buffer, PWM_CHAN_COUNT);
    }
}

uint16_t RCOutput_ROS::read(uint8_t chan)
{
    return _pulse_buffer[chan];
}


void RCOutput_ROS::read(uint16_t* period_us, uint8_t len)
{
    for (int i = 0; i < len; i++) {
        period_us[i] = read(i);
    }
}
#endif
