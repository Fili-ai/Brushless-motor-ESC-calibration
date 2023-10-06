#include "propeller_class.hpp"
#include "ESC_class.hpp"
#include <pigpio.h>
#include <iostream>

int Propeller::get_speed(){

    /** 
     * function to get the speed of the propeller
     * 
     * @return speed of the propeller
     */

    return this->speed;
}

int Propeller::set_speed(int value){

    /** 
     * function to set the speed of the propeller
     * 
     * @param value new speed to set 
     * @return 1 if all goes fine 0 otherwise
     */


    int min = this->get_min_pulse();
    int max = this->get_max_pulse();
    int pin = this->get_pin();
    if(value >= min && value <= max){
        this->speed = value;
        
        gpioServo(pin, this->speed);

        return 0;
    }
    else{
        std::cout << "Value out of range\n";
        return 1;
    }
}