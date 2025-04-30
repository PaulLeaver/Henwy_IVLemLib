#include "main.h"
#include "robodash/api.h"

rd::Selector Match_autos({
	{"Red Solo Winpoint", &RedPosWP},
	{"Blue Solo Winpoint", &BluePosWP},
	{"Red five ring", &Red4Ring},
	{"Blue five ring", &Blue4Ring},
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
	// Match_autos.focus();
	console.println("Initializing robot...");
	preroller.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
	hooks.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
	chassis.calibrate(); // calibrate sensors
	// sorter.disable_gesture();
	pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            console.printf("X: %f", chassis.getPose().x); // x
            console.printf("Y: %f", chassis.getPose().y); // y
            console.printf("Theta: %f", chassis.getPose().theta); // heading
			// console.printf("distance: %f", sorter.get_proximity()); // heading
			// console.printf("color: %f", sorter.get_hue());
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

static bool firstauto = true;
void autonomous() {
	if (firstauto){
		firstauto = false;
		RedPosWP();
		// BluePosWP();
		// skills();
	  }
	  else{
		Action_Period();
	  }
}


void opcontrol() {
	Action_Period();
}
