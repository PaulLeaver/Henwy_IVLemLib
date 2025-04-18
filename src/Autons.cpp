#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/rtos.hpp"

ASSET(Ring4_txt)
ASSET(Ring4Blue_txt)

float defaultMaxSpeed = 6;
int defaultTimeout = 3000;



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
    chassis.setPose(-48.903, 31.642, 75);
    Doinker.set_value(HIGH);
    moveRelative(33,127,950);
    delay(950);
    Doinker.set_value(LOW);
    moveRelative(-12,127,2000);
    delay(1000);
    Doinker.set_value(HIGH);
    chassis.moveToPose(-45,6,0, 1800, {.forwards = false,.horizontalDrift = 8, .lead = 0.4,.maxSpeed = 100 },false );
    Clamp.set_value(HIGH);
    pros::Task intake(RintakeTask);
    preroller.move(127);
    hooks.move(127);
    chassis.moveToPoint(-47.825,48.094, 1500, {.maxSpeed = 80},false);
    chassis.turnToHeading(-55, 1000);
    chassis.moveToPoint(-56,57, 1500, {.maxSpeed = 80},false);
    // chassis.moveToPose(-58 ,53,-45, 1500, {.maxSpeed = 100},false);
    chassis.moveToPoint(-22.742,47.016, 1500, {.maxSpeed = 100});
    delay(950);
    Doinker.set_value(LOW);
    chassis.moveToPose(-59,25,180, 2000, {.forwards = false,.horizontalDrift = 8, .lead = 0.4,.maxSpeed = 100 },false );
    chassis.moveToPoint(-58.613,-56.013, 1500, {.maxSpeed = 100});
    chassis.turnToHeading(-55, 1000);



}

void BluePosWP(){

    
}


void Red4Ring(){
    
    
}

void Blue4Ring(){

}


void skills(){

}
void DriveForward(){
    moveRelative(4,60,1000);
}

void Action_Period(){
    moveRelative(4,60,1000);
}