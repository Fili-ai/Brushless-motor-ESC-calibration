#include<pigpio.h>
#include<iostream>
#include <csignal> // For std::signal
#include <cstdlib> // For std::exit

#include "propeller_class.hpp"

using namespace std; 

// Signal handler function: to change because doesn't support passing argument
void signalHandler(int signal) {
    if (signal == SIGINT) {

        std::cout << "\nExiting..." << std::endl;
        // Perform cleanup or other necessary tasks here
        gpioPWM(gpio_pin, 0);
        gpioTerminate();
        std::exit(0); // Exit the program
    }
}

void test_duty_cycle( Propeller propeller){
    cout << "\n------------ Duty Cycle test ---------------- \n";

    int gpio_pin = propeller.get_pin();
    int min_pulse_width = propeller.get_min_pulse();
    int max_pulse_width = propeller.get_max_pulse();
    unsigned dt = 0;

    cout << "Values between " << min_pulse_width << " and " << max_pulse_width << endl;
    while (cin >> dt){
        propeller.set_speed(dt);
    }
}


int main(){
    int init = gpioInitialise();
    int gpio_pin; 
    
    if (init < 0)
    {
        cerr << "Error in initialising PWM, error: "<< init << endl; 
        return 1;
    }

    cout << "Insert pin: ";
    cin >> gpio_pin;

    // Set up the signal handler
    std::signal(SIGINT, signalHandler);    

    // Propeller initialitation 
    Propeller propeller(gpio_pin, false, true);

    // propeller.arm();
    test_duty_cycle(propeller);

    gpioTerminate();

    return 0;
}
