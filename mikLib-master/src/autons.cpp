#include <string>
#include "vex.h"

void default_constants() {
    // Each controller constant in the form of throttle, turn (deadband, min_output, curve_gain), desaturate_bias.
    chassis.set_control_constants(5, 10, 1.019, 5, 10, 1.019, 0.5);

    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI, slew).
    chassis.set_drive_constants(8, 1.5, 0, 10, 0, 2);
    chassis.set_heading_constants(10, .4, 0, 1, 0, 0);
    chassis.set_turn_constants(12, .4, .03, 3, 15, 0);
    chassis.set_swing_constants(12, .4, .01, 2, 15, 0);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(1, 200, 3000);
    chassis.set_drive_exit_conditions(2, 200, 5000);
    chassis.set_swing_exit_conditions(1, 200, 3000);

    constants.boomerang_lead = .5;
    constants.boomerang_drift = 2;
}

/* When creating autons with odometry, use a path planner, https://path.jerryio.com/.
If your robot is not lining up with the points, double check you set up your odometry correctly */

std::string blue_left_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue left winpoint";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }    

    // Place start of autonoumous here
    
    return "";
}
std::string blue_left_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue left sawp";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string blue_left_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue left elim";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string blue_right_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue right winpoint";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string blue_right_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue right sawp";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string blue_right_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue right elim";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}

std::string red_left_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red left winpoint";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string red_left_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red left sawp";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string red_left_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red left elim";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string red_right_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red right winpoint";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(-38.172, -171.441, 35.0);

        return "";
    }
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
std::string red_right_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red right sawp";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string red_right_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red right elim";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string skills(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "skills";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in

        return "";
    }

    // Place start of autonoumous here

    return "";
}
