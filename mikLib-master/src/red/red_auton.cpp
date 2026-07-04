#include "vex.h"

using namespace vex;
using namespace std;

std::string red_auton(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red right winpoint";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(-38.172, -171.441, 35.0);

        return "";
    }
    odom_constants();
    // start of autonomous here
    
    // setting up the robot to flip the toggle
   chassis.turn_to_point(-4.018, -124.563);
   chassis.drive_to_point(-4.018, -124.563);
   wait(100, vex::msec);
    flip_toggle();

    // scoring the preloaded pin
    chassis.turn_to_point(-60.101, -120.554);
    chassis.drive_to_point(-60.101, -120.554);
    // btw i have truw set as claw open in my code
    claw_to_default();

    // getting the neutral pin right next to the preloaded pin
    chassis.turn_to_point(-59.384, -173.617);
    chassis.drive_to_point(-59.384, -173.617);
    close_claw();
    assembly.lift_motors.spin_for(1, vex::voltageUnits::volt, 200, vex::timeUnits::msec);

    // scoring the neutral pin
    chassis.turn_to_point(-60.101, -120.554);
    chassis.drive_to_point(-60.101, -120.554);
    claw_to_default();

    // grabbing the neutral pin on the other side of the alliance goal
    chassis.turn_to_point(-120.334, -118.403);
    chassis.drive_to_point(-120.334, -118.403);
    close_claw();
    assembly.lift_motors.spin_for(2, vex::voltageUnits::volt, 200, vex::timeUnits::msec);

    // scoring the second neutral pin
    chassis.turn_to_point(-60.101, -120.554);
    chassis.drive_to_point(-60.101, -120.554);
    claw_to_default();

    // getting the pin for the new neutral goal
    chassis.turn_to_point(-60.272, -58.933);
    chassis.drive_to_point(-60.272, -58.933);
    close_claw();

    // driving to the new neutral goal to score the pin
    chassis.turn_to_point(58.933, -118.535);
    chassis.drive_to_point(58.933, -118.535);
    claw_to_default();

    // optional extra neutral pin grabbing
    chassis.turn_to_point(58.933, -173.45);
    chassis.drive_to_point(58.933, -173.45);
    close_claw();
    assembly.lift_motors.spin_for(1, vex::voltageUnits::volt, 200, vex::timeUnits::msec);
    
    // optional scoring the extra neutral pin
    chassis.turn_to_point(58.933, -118.535);
    chassis.drive_to_point(58.933, -118.535);
    claw_to_default();
    vex::wait(100, vex::msec);

    return "";
}