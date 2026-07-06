// add in PID constants here
// everything here is inputted straight from the video
// all the numbers need to be changed and tuned
void odom_constants() {
    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI, slew).
    chassis.set_drive_constants(8, 1.5, 0, 10, 0, 2);
    chassis.set_heading_constants(10, .4, 0, 1, 0, 0);
    chassis.set_turn_constants(12, .4, .03, 3, 15, 0);
    chassis.set_swing_constants(12, .4, .01, 2, 15, 0);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(3, 100, 3000); // edited for faster auton speed but less precision
    chassis.set_drive_exit_conditions(2, 200, 5000);
    chassis.set_swing_exit_conditions(1, 200, 3000);

    constants.boomerang_lead = .5;
    constants.boomerang_drift = 2;
}

// tweaked constants for when the robot is carrying a mobile goal, these are used in the mogo auton
void mogo_constants() {
    odom_constants();
    mogo_offsets();
}

void mogo_offsets() {
    chassis.set_tracking_offsets(0, 1);
}