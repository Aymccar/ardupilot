#pragma once
#include <AP_HAL.h>

class Dev_Backend {
public: 
    bool init(); //Find the serial port
    void start(); //
    int update();

private:
    void do_something();

    AP_HAL::OwnPtr<AP_HAL::UARTDriver> _driv;
};
