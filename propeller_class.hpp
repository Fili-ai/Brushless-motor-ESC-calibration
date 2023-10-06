#include "ESC_class.hpp"

class Propeller : public ESC{
    private: 
        int speed = 0;

    public:
        Propeller(int pin, bool need_cal, bool just_cal) : ESC(pin, need_cal, just_cal){};
        int set_speed(int value);
        int get_speed();
};