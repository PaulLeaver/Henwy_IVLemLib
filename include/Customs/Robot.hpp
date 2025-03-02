#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/optical.hpp"
#include "pros/gps.hpp"
#include "robodash/api.h"
#include "pros/distance.hpp"

using namespace pros;
using namespace lemlib;

extern Controller controller;

extern MotorGroup driveLeft;
extern MotorGroup driveRight;

extern Motor hooks;
extern Motor preroller;
extern MotorGroup intake;
extern Motor LB;

extern Imu imu;
extern Optical sorter;

extern adi::Pneumatics Clamp;
extern adi::Pneumatics Rushmech;
extern adi::Pneumatics Doinker;

extern Drivetrain drivetrain;

extern TrackingWheel horizontal_tracking_wheel;
extern TrackingWheel vertical_tracking_wheel;

extern Chassis chassis;

extern rd::Console console;