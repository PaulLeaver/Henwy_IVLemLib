#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include <sys/_intsup.h>
#include "robodash/api.h"

using namespace pros;
using namespace lemlib;

rd::Console console;

Controller controller(E_CONTROLLER_MASTER);
// motor groups
pros::MotorGroup leftMotors({-7,6, -8}, pros::MotorGearset::blue); // left side motors in ports 6,7,8
pros::MotorGroup rightMotors({14, -15, 18}, pros::MotorGearset::blue); // right side motors in ports 14,15,18

Motor LB(10, pros::MotorGearset::green); // arm motor on port 10
Motor hooks(-11, pros::MotorGearset::blue); // right intake motor on port 11
Motor preroller(-20, pros::MotorGearset::green); // right intake motor on port 20
MotorGroup intake({-11, -20}, pros::MotorGearset::blue); // intake motors on ports 11,20

// Inertial Sensor on port 1
pros::Imu imu(1);

adi::Pneumatics Clamp('e', LOW);
adi::Pneumatics Rushmech('c', LOW);
adi::Pneumatics Doinker('b', LOW);

//optical sensor for color sort in port 9
Optical sorter(9);
Distance distsort(17);

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 5, not reversed
pros::Rotation horizontalEnc(-5);
// vertical tracking wheel encoder. Rotation sensor, port 3, reversed
pros::Rotation verticalEnc(3);
// horizontal tracking wheel. 2" diameter, .5" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, -.5);
// vertical tracking wheel. 2" diameter, 1" offset, right of the robot (positive)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, 1);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              13, // 13 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              600, // drivetrain rpm is 600
                              8 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// sensors for odometry
lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

ExpoDriveCurve throttle_curve(6.35, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.025 // expo curve gain
);

// input curve for steer input during driver control
ExpoDriveCurve steer_curve(6.35, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.025 // expo curve gain
);


// create the chassis
Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);