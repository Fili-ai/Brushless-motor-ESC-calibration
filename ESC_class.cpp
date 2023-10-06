#include "ESC_class.hpp"

#include <iostream>
#include <pigpio.h>
#include <stdexcept>


ESC::ESC(int pin, bool need_cal, bool just_cal)
{
    /**
     * Class constructor 
     *
     * @param pin is the pin to assign;
     * @param need_cal if need to be calibrate;
     * @param just_cal if is just calibrate;
     */

    set_pin(pin);
    
    // Set the GPIO pin to ESC mode
    gpioSetMode(this->pin, PI_OUTPUT);
    
    need_calibration(need_cal, just_cal);
}

ESC::~ESC(){
    gpioServo(this->pin, 0);
}

void ESC::set_pin(int pin){
    /**
     * Function to set the pin of the ESC's object created.
     *
     * @param pin is the pin to assign;
     */
    if(pin == 12 || pin == 13 || pin == 18 || pin == 19)
        this->pin = pin; 
    else{
        throw std::out_of_range("Pin is not a pwm");
    }
}

int ESC::get_pin(){
    /**
     * Function to get the pin of the ESC's object created.
     *
     * @return pin assigned;
     */

    return this->pin; 
}

int ESC::get_max_pulse()
{
    return this-> max_pulse_width;
}

int ESC::get_min_pulse()
{
    return this-> min_pulse_width;
}

void ESC::need_calibration(bool need_cal, bool just_cal){
    /**
     * Function to set the status of calibration.
     *
     * @param need_cal if need to be calibrate;
     * @param just_cal if is just calibrate;
     */

    if(need_cal){
        calibration();
        this->calibration_done = true;
    }
    if(!need_cal){
        if(just_cal){
            this->calibration_done = true;
            arm();
        }
    }

}

bool ESC::get_calibration(){
    /**
     * Function to get the status of calibration.
     *
     * @return a bool if the calibration was done (true) or not (false);
     */

    return this->calibration_done; 
}

void ESC::calibration(){
    /**
     * Function to calibrate ESC 30A following the chapter "Throttle Range Setting" of ESC Docs.
     */

    std::cout << "\n------------ ESC Calibration ----------------";
    std::cout << "\nDisconnect the battery to the ESC and press Enter to continue." << std::endl;
    std::cin.ignore(1000,'\n');
    std::cin.get();

    gpioServo(this->pin, this->max_pulse_width);
    std::cout << "Connect the battery to the ESC, wait the 3-beep and press Enter to continue.";
    std::cin.get();

    time_sleep(2);

    gpioServo(this->pin, this->min_pulse_width);

    time_sleep(1);
    std::cout << "\n------------ ESC Calibration complete ----------------" << std::endl;

    gpioServo(this->pin, this->min_pulse_width);

}

void ESC::arm(){

    /**
     * Function to arm ESC 30A.
     */
    if(!this->calibration_done)
        std::cout << "ESC not calibrated, calibrate it and retry" << std::endl;
    else{
        std::cout << "\n------------ ESC arming ----------------";
            
        std::cout << "\nDisconnect the battery to the ESC and press Enter to continue." << std::endl;
        std::cin.ignore(1000,'\n');
        std::cin.get();

        gpioServo(this->pin, this->min_pulse_width);

        std::cout << "\nConnect the battery to the ESC, wait the long-beep and press Enter to continue.";
        std::cin.get();

        std::cout << "\n------------ ESC armed ----------------";
    }
}