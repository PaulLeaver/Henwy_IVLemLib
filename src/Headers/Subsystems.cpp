#include "main.h"
#include "pros/adi.hpp"
#include "pros/adi.h"
#include "pros/misc.h"

 int wallMech = 0;
static bool Clamptoggle{false};
static bool Rushtoggle{false};
static bool Doinkertoggle{false};
int startTime;
bool isJamHandled = true;
bool colorSortON = true;

// void ColorSortControl(){
// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
//   colorSortON = true;
// } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
//   colorSortON = false;
// }


// }
void setIntakes() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      hooks.move_velocity(600);
      preroller.move_velocity(200);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      hooks.move_velocity(-600);
      preroller.move_velocity(-200);
    } else {
      hooks.move_velocity(0);
      preroller.move_velocity(0);
    }
  }

 void controlIntake() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        startTime = pros::millis();
    }
    int currentIntakeVelocity = hooks.get_actual_velocity();
    // When R1 is pressed, run the intake forward
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        // If the motor is powered but hasn't moved within the first 500ms, reverse briefly
        if (currentIntakeVelocity == 0 && !isJamHandled && pros::millis() - startTime > 300 ){
            // Reverse the motor briefly to un-jam
            hooks.move(-127);
            preroller.move(-127);
            pros::delay(100); // Reverse for 0.25 seconds
            hooks.move(127);
            preroller.move(127);
            isJamHandled = true; // Jam handling is done, don't trigger again
        } else {
            // Normal operation for forward intake
            hooks.move(127);
            preroller.move(127);
            isJamHandled = false; // Reset jam handling flag
        }
    }
    // When L1 is pressed, run the intake backward
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        hooks.move(-127);
        preroller.move(-127);
    }
    // Otherwise, stop the intake and preroller
    else {
        hooks.brake();
        preroller.brake();
    }
  }

void setClamp() {
  if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
    if (!Clamptoggle) {
      Clamp.set_value(true);
      Clamptoggle = !Clamptoggle;
    } else {
      Clamp.set_value(false);
      Clamptoggle = !Clamptoggle;
    }
  }
}
