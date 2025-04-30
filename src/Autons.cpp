#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/rtos.hpp"


void moveRelative(float distance, float maxSpeed, int timeout) {
    double headingRadians = chassis.getPose(true).theta;
    double startingX = chassis.getPose().x;
    double startingY = chassis.getPose().y;
    double deltaX = distance * sin(headingRadians);
    double deltaY = distance * cos(headingRadians);
    double newX = startingX + deltaX;
    double newY = startingY + deltaY;
    if (distance > 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxSpeed});
    }
    else if (distance < 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxSpeed});
    }
};



void RedPosWP(){
   

}

void BluePosWP(){
    
}


void Red4Ring(){
}

void Blue4Ring(){

}


void skills(){
    chassis.setPose(-56.455, 64.929, -90);
    // pros::Task intake(RintakeTask);
    preroller.move(127);
    chassis.swingToPoint(0,0, DriveSide::RIGHT, 1100,{.forwards = false,.maxSpeed = 90},false);
    chassis.moveToPoint(-40,64.929, 800, {.forwards = false,.maxSpeed = 80});
    chassis.moveToPoint(-21.393,45.128, 800, {.forwards = false,.maxSpeed = 80},false);
    Clamp.set_value(HIGH);
    pros::Task intake(RintakeTask);
    chassis.moveToPoint(-45.937,46.858, 1500, {.maxSpeed = 80});
    chassis.moveToPoint(-18.696,27.889, 1500, {.maxSpeed = 80});
    delay(1000);
    chassis.moveToPose(11.511,8,90, 2000, {.horizontalDrift = 8, .lead = 0.6,.maxSpeed = 60 },false );\
    delay(1000);
    chassis.moveToPoint(-34.339,34.362, 1500, {.forwards = false,.maxSpeed = 80},false);
    chassis.moveToPoint(2,46.206, 1500, {.maxSpeed = 80});
    chassis.moveToPoint(-59.074,62.501, 1500, {.forwards = false,.maxSpeed = 80},false);
    Clamp.set_value(LOW);
    intake.suspend();
    hooks.move(127);
    delay(500);
    target = states[1];
    chassis.moveToPose(7,61.5,0, 3000, { .horizontalDrift = 8, .lead = 0.2},false);
    hooks.move_relative(-20,127);
    delay(800);
    target = states[2];
    delay(900);
    target = states[0];
    moveRelative(-10,60,1000);
    hooks.brake();
    chassis.turnToHeading(90, 500);
    chassis.moveToPoint(23.281, 52, 1000, {.maxSpeed = 80});
    chassis.turnToHeading(0, 500);
    chassis.moveToPoint(23.581,24.832, 1500, {.forwards = false,.maxSpeed = 80},false);
    Clamp.set_value(HIGH);
    // intake.Resume();
    hooks.move(127);
    chassis.moveToPoint(47.382, 23.821, 1000, {.maxSpeed = 80});
    chassis.moveToPoint(46.573, 47.016, 1000, {.maxSpeed = 80});
    chassis.moveToPose(56.732,61.5,90, 3000, { .horizontalDrift = 8, .lead = 0.2},false);
    chassis.moveToPoint(65.633, 64.434, 1000, {.maxSpeed = 80});
    chassis.moveToPoint(58.35, 56.343, 1000, {.forwards = false,.maxSpeed = 80});
    chassis.turnToHeading(-135, 500);
    chassis.moveToPoint(65.633, 64.434, 1000, {.forwards = false,.maxSpeed = 80});
    Clamp.set_value(LOW);
    moveRelative(10,60,1000);
}
void DriveForward(){
    moveRelative(4,60,1000);
}

void Action_Period(){
    moveRelative(10,60,1000);
}