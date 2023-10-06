cmake_minimum_required(VERSION 3.9.1)

set(CMAKE_CXX_STANDARD 17)

project(Tests_cpp)

add_executable(test_duty_cycle pwm.cpp ESC_class.cpp propeller_class.cpp)

target_link_libraries(test_duty_cycle pigpio rt)
