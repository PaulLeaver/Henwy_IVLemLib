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

bool allow_breaking = false; // set to true to have the robot pause at every step
void log(){ // logs information about the robot
  std::cout << // function that logs stuff
  "x: " << chassis.getPose().x // x position
  << " y: " << chassis.getPose().y // y position
  << " angle: " << chassis.getPose().theta // direction
  << "\npreroller effic: " << preroller.get_efficiency() // preroller efficiency
  << " volt:" << preroller.get_voltage() // preroller voltage
  //<< "\nTime:" << timer.value() // Time that has gone by since start
  << std::endl; // ends the line
  if (allow_breaking) { // allows the robot to break its process while driving
    char input; // defines the input for the bot
    std::cout << "press any key to continue" << std::endl;
    std::cin >> input; // takes input
  }
}

void RedPosWP(){
    chassis.setPose(-54.837, 12.223, 180);


    //Alliance Stake scoring 
    chassis.swingToPoint(-24.484,19.011, DriveSide::RIGHT, 1100,{.forwards = false,.maxSpeed = 90});
     delay(700);
    target = states[2];
    delay(600);
    target = states[0];


    //Getting the 1st Goal
    chassis.moveToPose(-24.484,23.011,-90, 1500, {.forwards = false,.horizontalDrift = 8, .lead = 0.4,.maxSpeed = 100 });
    delay(1100);
    Clamp.set_value(HIGH);
    // hooks.move_relative(100,-127);

    pros::Task intake(RintakeTask);
    preroller.move(127);
    hooks.move(127);
    //Ring 1
    chassis.turnToHeading(0, 400);
    chassis.moveToPoint(-28.011,47.24, 2000, {.maxSpeed = 105});

    //Ring 2
    chassis.turnToHeading(90, 500);
    chassis.moveToPoint(-9,43.43, 2000, {.maxSpeed = 80});

    //Moving back to drop goal
    delay(300); 
    chassis.moveToPoint(-31.912,48.094, 2000, {.forwards = false, .maxSpeed = 100});
    //Moving to the middle of the side
    chassis.moveToPoint(-43.464,-5, 2000, {.maxSpeed = 90});
    preroller.move(-127);
    Clamp.set_value(LOW);
    chassis.turnToHeading(-45, 1000);
    hooks.brake();
    //moving to get the 2nd goal
    preroller.move(127);
    chassis.moveToPoint(-23.821,-23.918, 1000, {.forwards = false, .maxSpeed = 80});
    delay(800);
    Clamp.set_value(HIGH);
    hooks.move(127);    
    //getting the 3rd ring
    chassis.moveToPoint(-14.551,-55.652, defaultTimeout, {.maxSpeed = 127});
    //touching the ladder
    chassis.moveToPoint(-23.551,-18, 2000, {.maxSpeed = 95});
    delay(1100);
    target = states[2];
    return;
}

void BluePosWP(){

    chassis.setPose(54.837, 12.223, 180);


    //Alliance Stake scoring 
    chassis.swingToPoint(18,17, DriveSide::LEFT, 1300,{.forwards = false,.maxSpeed = 90});
     delay(700);
    target = states[2];
    delay(600);
    target = states[0];


    //Getting the 1st Goal
    chassis.moveToPose(24.484,23.011,90, 1500, {.forwards = false,.horizontalDrift = 8, .lead = 0.4,.maxSpeed = 100 });
    delay(1100);
    Clamp.set_value(HIGH);
    // hooks.move_relative(100,-127);

    pros::Task intake(BintakeTask);
    preroller.move(127);
    hooks.move(127);
    //Ring 1
    chassis.turnToHeading(0, 400);
    chassis.moveToPoint(28.011,47.24, 2000, {.maxSpeed = 105});

    //Ring 2
    chassis.turnToHeading(-90, 500);
    chassis.moveToPoint(9,43.43, 2000, {.maxSpeed = 80});

    //Moving back to drop goal
    delay(300); 
    chassis.moveToPoint(31.912,48.094, 2000, {.forwards = false, .maxSpeed = 100});
    //Moving to the middle of the side
    chassis.moveToPoint(43.464,-5, 2000, {.maxSpeed = 90});
    preroller.move(-127);
    Clamp.set_value(LOW);
    chassis.turnToHeading(45, 1000);
    hooks.brake();
    //moving to get the 2nd goal
    preroller.move(127);
    chassis.moveToPoint(23.821,-23.918, 1000, {.forwards = false, .maxSpeed = 80});
    delay(900);
    Clamp.set_value(HIGH);
    hooks.move(127);    
    //getting the 3rd ring
    chassis.moveToPoint(14.551,-55.652, defaultTimeout, {.maxSpeed = 127});
    //touching the ladder
    chassis.moveToPoint(20,-16, 2000, {.maxSpeed = 95});
    delay(1100);
    target = states[2];
    return;
}


void Red4Ring(){
    chassis.setPose(-52.14, 23.821, 270);
    moveRelative(-29,80,650);
    delay(650);
    Clamp.set_value(HIGH);
    pros::Task intake(RintakeTask);
    preroller.move(127);
    hooks.move(127);
    chassis.turnToHeading(40,500);
    chassis.moveToPose(-13.5,58.163,0,2000, {.horizontalDrift = 8, .lead = 0.4,.maxSpeed = 80 });
    chassis.turnToHeading(270,1000);
    chassis.moveToPoint(-30.024,41.082, 2000, {.maxSpeed = 100});
    target = states[2];
    chassis.moveToPoint(-20,18, 2000, {.maxSpeed = 80});
    // chassis.moveToPoint(-56,53, 2000, {.maxSpeed = 80});
    // chassis.turnToHeading(-45,500);
    // delay(650);
    // Doinker.set_value(HIGH);
    // moveRelative(5,80,1000);
    // chassis.turnToHeading(45, 1000,{.maxSpeed = 80});

    
}

void Blue4Ring(){
    chassis.setPose(54.837, 12.223, 180);


    //Alliance Stake scoring 
    chassis.swingToPoint(18,17, DriveSide::LEFT, 1800,{.forwards = false,.maxSpeed = 90});
     delay(700);
    target = states[2];
    delay(600);
    target = states[0];
    chassis.moveToPose(24.484,23.011,90, 1500, {.forwards = false,.horizontalDrift = 8, .lead = 0.4,.maxSpeed = 100 });
    delay(1100);
    Clamp.set_value(HIGH);
 pros::Task intake(BintakeTask);
 preroller.move(127);
 hooks.move(127);
 chassis.turnToHeading(-50,1000);
 chassis.moveToPose(15,60,0,2000, {.horizontalDrift = 8, .lead = 0.4,.maxSpeed = 80 });
 chassis.turnToHeading(90,1000);
 chassis.moveToPoint(30.024,41.082, 2000, {.maxSpeed = 100},false);
 target = states[2];
    chassis.moveToPoint(20,18, 2000, {.maxSpeed = 80});
//  chassis.turnToHeading(45,500);
//  delay(650);
//  Doinker.set_value(HIGH);
//  moveRelative(4,80,1000);
//  chassis.turnToHeading(-45, 1000,{.maxSpeed = 80});
}

void RedGoalRush(){
    chassis.setPose(-56.455, -33.358, 110);
    preroller.move(127);
    Doinker.set_value(HIGH);
    moveRelative(32,127,900);
    delay(850);
    Doinker.set_value(LOW);
    moveRelative(-12,127,2000);
    delay(1000);
    Doinker.set_value(HIGH);
    chassis.moveToPoint(-0,-46.303, 1100, {.forwards = false, .maxSpeed = 80});
    delay(1100);
    Doinker.set_value(LOW);
    Clamp.set_value(HIGH);
    pros::Task intake(RintakeTask);
    preroller.move(127);
    hooks.move(127);
    chassis.moveToPoint(-58.376,-55.328, 2000, { .maxSpeed = 80});
    chassis.turnToHeading(45,1000);
    delay(900);
    Clamp.set_value(LOW);
    moveRelative(10,127,900);
    chassis.turnToHeading(200,1000);
    chassis.moveToPoint(-35,-18.536, 2000, {.forwards = false, .maxSpeed = 80});
    delay(800);
    Clamp.set_value(HIGH);
    chassis.moveToPoint(-64.455, -24.358, 2000, { .maxSpeed = 80});
    chassis.moveToPose(-30,-46.303,90, 1500, {.forwards = false,.horizontalDrift = 8, .lead = 0.4,.maxSpeed = 100 });

}

void BlueGoalRush(){
    chassis.setPose(53.586, -61.497, 285);
    preroller.move(127);
    Doinker.set_value(HIGH);
    moveRelative(32,127,900);
    delay(850);
    Doinker.set_value(LOW);
    moveRelative(-12,127,2000);
    delay(1000);
    Doinker.set_value(HIGH);
    chassis.moveToPoint(0,-46.303, 1100, {.forwards = false, .maxSpeed = 80});
    delay(1100);
    Doinker.set_value(LOW);
    Clamp.set_value(HIGH);
    pros::Task intake(BintakeTask);
    preroller.move(127);
    hooks.move(127);
    chassis.moveToPoint(60,-60, 4000, { .maxSpeed = 80});
    chassis.turnToHeading(-90,1000);
    delay(900);
    Clamp.set_value(LOW);
    moveRelative(10,127,900);
    chassis.turnToHeading(135,1000);
    chassis.moveToPoint(22,-20, 800, {.forwards = false, .maxSpeed = 80}, false);
    Clamp.set_value(HIGH);
    return;
    chassis.moveToPoint(45, 40, 2000, { .maxSpeed = 80});
    chassis.moveToPose(30,-46.303,90, 1500, {.forwards = false,.horizontalDrift = 8, .lead = 0.4,.maxSpeed = 100 });

}

void RingRushRed(){
    chassis.setPose(-58, 27.5, 68);
    Rushmech.set_value(HIGH);
    moveRelative(37,127,2000);
    // chassis.turnToHeading(110,500);
    // moveRelative(-6,60,1000);
    chassis.moveToPose(-36.945,41.767,90, 1500, {.forwards = false,.horizontalDrift = 8, .lead = .2,.maxSpeed = 120 },false);
    Rushmech.set_value(LOW);
    chassis.moveToPose(-21,16,-45, 1000, {.forwards = false,.horizontalDrift = 8, .lead = .8,.maxSpeed = 127, .minSpeed = 60 },false);
    Clamp.set_value(HIGH);
    chassis.swingToHeading(20, DriveSide::LEFT, 800,{.maxSpeed = 127});
    pros::Task intake(RintakeTask);
    preroller.move(127);
    hooks.move(127);
    chassis.moveToPoint(-19, 68, 2200, { .maxSpeed = 50});
    chassis.moveToPoint(-23.551,37.845, 2000, {.forwards = false, .maxSpeed = 100});
    chassis.moveToPoint(-68, 37.845, 3000, { .maxSpeed = 100});
    chassis.moveToPose(-64,1,190, 3000, {.horizontalDrift = 8, .lead = .4,.maxSpeed = 90});

}

void RingRushBlue(){
    chassis.setPose(58, 27.5, 292);
    Rushmech.set_value(HIGH);
    moveRelative(37,127,2000);
    // chassis.turnToHeading(110,500);
    // moveRelative(-6,60,1000);
    chassis.moveToPose(36.945,41.767,-90, 1500, {.forwards = false,.horizontalDrift = 8, .lead = .2,.maxSpeed = 120 },false);
    Rushmech.set_value(LOW);
    chassis.moveToPose(21,16,45, 1000, {.forwards = false,.horizontalDrift = 8, .lead = .8,.maxSpeed = 127, .minSpeed = 60 },false);
    Clamp.set_value(HIGH);
    chassis.swingToHeading(-20, DriveSide::RIGHT, 800,{.maxSpeed = 127});
    pros::Task intake(BintakeTask);
    //hooks.move_relative(100, -127);
    preroller.move(127);
    hooks.move(127);
    chassis.moveToPoint(15, 70, 2200, { .maxSpeed = 50});
    chassis.moveToPoint(23.551,37.845, 2000, {.forwards = false, .maxSpeed = 100});
    chassis.moveToPoint(68, 37.845, 3000, { .maxSpeed = 100});
    return;
    chassis.moveToPose(64,15,190, 3000, {.horizontalDrift = 8, .lead = .4,.maxSpeed = 90});
}

void skills(){
    chassis.setPose(-59.25,0,270);
    // put ring on stake
    target = states[2];
    delay(750);
    target = states[0];
    // drive to get mobile goal
    delay(750);
    chassis.moveToPose(-46,27,180, 3500, {.forwards = false,.horizontalDrift = 8, .lead = 0.65, });
    delay(1200);
    pros::Task intake(RintakeTask);
    Clamp.set_value(HIGH);
    // turn to get first ring
    // chassis.turnToHeading(0);
    delay(500);
    preroller.move(127);
    hooks.move(127);
    // chassis.turnToHeading(180, defaultTimeout);
    intake.suspend();
    chassis.moveToPoint(-19,23.281, 2000, {.maxSpeed = 80},false);
    delay(500);
    target = states[1];
    chassis.moveToPose(7,61.5,0, 3000, { .horizontalDrift = 8, .lead = 0.2},false);
    hooks.move_relative(-20,127);
    delay(800);
    target = states[2];
    delay(900);
    target = states[0];
    moveRelative(-10,60,1000);
    intake.resume();
    // turn to second ring
    hooks.move(127);
    preroller.move(127);
    chassis.turnToHeading(-90, 500);
    chassis.moveToPoint(-23.281, 52, 1000, {.maxSpeed = 80});
    // turn to third ring
    chassis.turnToHeading(-90, 1000);
    chassis.moveToPoint(-45.016, 51, 2000,{.maxSpeed = 80});
    delay(1000);
    hooks.move_relative(360,-127);
    hooks.move(127);
    preroller.move(127);
    // drive to fourth ring
    chassis.moveToPoint(-58, 49.555, defaultTimeout,{.maxSpeed = 80});
    // turn to fifth ring
    chassis.moveToPoint(-45.016, 50, defaultTimeout,{.forwards = false,.maxSpeed = 80});
    chassis.moveToPose(-44.928, 64, 0, defaultTimeout,{.maxSpeed = 80});
    // drop mobile goal in corner
    chassis.turnToHeading(120,1000,{.maxSpeed=100},false);
    moveRelative(-10,100,1000);
    Clamp.set_value(LOW);
    moveRelative(8,80,2000);
    // drive to get second mobile goal
    chassis.turnToHeading(0, 1000);
    hooks.brake();
    chassis.moveToPoint(-53,-23.918, 1600, {.forwards = false, .maxSpeed = 90},false);
    Clamp.set_value(HIGH);
    // turn to sixth ring
    preroller.move(127);
    hooks.move(127);
    chassis.moveToPoint(-31,-20, defaultTimeout,{.maxSpeed = 80},false);
    intake.suspend();
    delay(500);
    target = states[1];
    chassis.moveToPose(-5,-60.5,180, 3000, { .horizontalDrift = 8, .lead = 0.4},false);
    hooks.move_relative(-20,127);
    delay(800);
    target = states[2];
    delay(1000);
    target = states[0];
    moveRelative(-10,60,1000);
    intake.resume();
    // turn to 7 ring
    chassis.moveToPoint(-30,-43, 1500,{.maxSpeed = 80});
    // turn to 8 ring
    chassis.moveToPoint(-47,-43, 2000,{.maxSpeed = 80});
    // 9th ring
    delay(1000);
    chassis.moveToPoint(-68,-43, 2000,{.maxSpeed = 80});
    //10th ring
    chassis.swingToHeading(180, DriveSide::RIGHT, 1000);
    chassis.moveToPose(-58, -63,180, 2000);
    //put the goal in corner
    chassis.swingToHeading(20, DriveSide::RIGHT, 1500,{},false);
    preroller.brake();
    hooks.brake();
    intake.suspend();
    Clamp.set_value(LOW);
    moveRelative(9,80,2000);
    //drive to middle
    chassis.moveToPoint(-3, -46.573, 2000,{.maxSpeed = 80});
    //pick up 11th ring and put on alliance stake
    preroller.move(127);
    chassis.moveToPoint(27.903, -23.558, 2000,{.maxSpeed = 80});
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(42,-28, 2000, {.forwards = false, .maxSpeed = 80});
    chassis.moveToPoint(64.158,-60, defaultTimeout, {.forwards = false, .maxSpeed = 100});
    moveRelative(6,80,1000);
    //grab 4th goal
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(53, 0, 1800,{.forwards = false,.maxSpeed = 80});
    delay(700);
    Clamp.set_value(HIGH);
    //ring 12
    chassis.turnToHeading(-45, 1000);
    preroller.move(127);
    hooks.move(127);
    chassis.moveToPoint(30.11,15.864, 1500,{.maxSpeed = 80});
    // //ring 13
    chassis.moveToPoint(23.109, 48.274, 1500,{.maxSpeed = 80});
    //put goal in corner
    chassis.turnToHeading(-150,1000);
    chassis.moveToPoint(64.374, 65.535, 1800,{.forwards = false,.maxSpeed = 100});
    Clamp.set_value(LOW);
    chassis.moveToPoint(23.109, 48.274, 1500,{.maxSpeed = 80});
    return;
}
void DriveForward(){
    moveRelative(4,60,1000);
}