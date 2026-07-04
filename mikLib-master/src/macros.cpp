void flip_toggle() {
    chassis.turn_to_point(-0.67, -173.45, {.angle_offset = 180});
    chassis.drive_to_point(-0.67, -173.45, {.min_voltage = 5});
    chassis.drive_to_point(-0.67, -163.45);
    chassis.drive_to_point(-0.67, -173.45, {.min_voltage = 5});
};

void claw_to_default() {
    assembly.chainbar_motors.spin_for(-.5, vex::voltageUnits::volt, 200, vex::timeUnits::msec);
    assembly.clamp_piston.set(true);
    assembly.chainbar_motors.spin_for(.5, vex::voltageUnits::volt, 200, vex::timeUnits::msec);
};

void close_claw() {
    assembly.clamp_piston.set(false)
};
