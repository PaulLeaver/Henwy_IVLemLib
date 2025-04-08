#include "main.h"
#include "robodash/api.h"

rd::Selector Match_autos({
	{"Red Solo Winpoint", &RedPosWP},
	{"Blue Solo Winpoint", &BluePosWP},
	{"Red five ring", &Red4Ring},
	{"Blue five ring", &Blue4Ring},
	{"Red Goal rush", &RedGoalRush},
	{"Blue Goal rush", &BlueGoalRush},
	{"Red Ring Rush", &RingRushRed},
	{"Blue Ring Rush", &RingRushBlue},
	{"Skills", &skills},
	{"Drive Forward", &DriveForward},
});

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	Match_autos.focus();
	console.println("Initializing robot...");
	preroller.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
	hooks.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
	chassis.calibrate(); // calibrate sensors
	sorter.disable_gesture();
	pros::Task liftControlTask(LBTask, "LB Task");
	pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            console.printf("X: %f", chassis.getPose().x); // x
            console.printf("Y: %f", chassis.getPose().y); // y
            console.printf("Theta: %f", chassis.getPose().theta); // heading
			console.printf("\nprox: ", (float)sorter.get_proximity());
            // delay to save resources
            pros::delay(50);
			console.clear();
        }
    });
}


void disabled() {

}


void competition_initialize() {

}


void autonomous() {
	// console.println("Running auton...");
	// console.focus();
	// Match_autos.run_auton();
	// skills();
	Blue4Ring();
	//RingRushBlue();
	//  BluePosWP();
	// BlueGoalRush();
}


void opcontrol() {
	  // controller
    // loop to continuously update motors
	
    while (true) {


        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        // move the chassis with curvature drive
        chassis.tank(leftY, rightY);
		
		controlIntake();
		setIntakes();
		setClamp();
		setDoinker();
		setLB();
		// pros::Task intake(BintakeTask);
        // delay to save resources
        pros::delay(10);
    }
}