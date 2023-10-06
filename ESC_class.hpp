#pragma once
class ESC{
    private:
        const unsigned min_pulse_width = 1000;
        const unsigned max_pulse_width = 2000;
        bool calibration_done = false;
        unsigned pin;
        
        void calibration();

    public: 
        ESC(int pin, bool need_cal, bool just_cal);
        ~ESC();

        void set_pin(int pin);
        int get_pin();

        int get_max_pulse();
        int get_min_pulse();

        void need_calibration(bool need_cal, bool just_cal);
        bool get_calibration();

        void arm();

};