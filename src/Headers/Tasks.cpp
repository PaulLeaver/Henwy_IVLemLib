#include "main.h"
#include "pros/rtos.hpp"

// void odomTask() {
//     console.printf("The robot's heading is %f\n", imu.get_heading());
//     console.printf("The robot's x position is %f\n", chassis.getPose().x);
//     console.printf("The robot's y position is %f\n", chassis.getPose().y);
//     pros::delay(50);
// }

void LBTask() {
    while (true) {
        liftControl();
        pros::delay(10);
    }
}
// bool colorSortON = true;
void BintakeTask() {
    uint32_t lastCheckTime = pros::millis();
    sorter.set_integration_time(10);
    sorter.set_led_pwm(100);
    while (true) {
        // Run the intake motor
        int hue = sorter.get_hue();
        int distance = distsort.get_distance();
        // if(proximity < 100){
        if (((hue >= 0 && hue <= 38) || hue >= 340 ) ) {
            // Reverse the intake motor if the color matches
            pros::delay(65);
            hooks.move_velocity(-600);
            preroller.move_velocity(-200);
            pros::delay(150); // Delay to allow the motor to reverse
            hooks.move_velocity(600); // Resume normal operation
            preroller.move_velocity(200);
        }
    // }
        // Check if a certain amount of time has passed since the last speed check
        if (pros::millis() - lastCheckTime >= 300) { // Check every 300 ms
            // Check if the hook motor is going too slow
            if (hooks.get_actual_velocity() < 75 && currState != 1) {
                // Reverse the hook motor if it is going too slow
                hooks.move_velocity(-600);
                pros::delay(150); // Delay to allow the motor to reverse
                hooks.move_velocity(600); // Resume normal operation

                // Reset the timer after reversing
                lastCheckTime = pros::millis();
            } else {
                // Reset the timer if no reversal is needed
                lastCheckTime = pros::millis();
            }
        }
        pros::delay(50); // Small delay to prevent excessive CPU usage
    }
}

void RintakeTask() {
    uint32_t lastCheckTime = pros::millis();
    sorter.set_integration_time(10);
    sorter.set_led_pwm(100);
    while (true) {
        // Run the intake motors
        int hue = sorter.get_hue();
        // if(proximity < 100){
        if (((hue >= 200 && hue <= 240))) {
            // Reverse the intake motor if the color matches
            hooks.move_velocity(-600);
            
            pros::delay(100); // Delay to allow the motor to reverse
            hooks.move_velocity(600); // Resume normal operation
            
        }
    // }
        // Check if a certain amount of time has passed since the last speed check
        if (pros::millis() - lastCheckTime >= 300) { // Check every 300 ms
            // Check if the hook motor is going too slow
            if (hooks.get_actual_velocity() < 75 && currState != 1) {
                // Reverse the hook motor if it is going too slow
                hooks.move_velocity(-600);
                pros::delay(150); // Delay to allow the motor to reverse
                hooks.move_velocity(600); // Resume normal operation

                // Reset the timer after reversing
                lastCheckTime = pros::millis();
            } else {
                // Reset the timer if no reversal is needed
                lastCheckTime = pros::millis();
            }
        }

        pros::delay(50); // Small delay to prevent excessive CPU usage
    }
}