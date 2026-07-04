#include "vex.h"


vex::brain Brain;
vex::controller Controller;


// mikLib v2.0 setup, if you are following along with video tutorials it is going to be slightly different


Chassis chassis(
   // Left drivetrain motors (left/right is looking from behind the robot)
   mik::motor_group({
       mik::motor(PORT3, false, blue_6_1, "left front motor"), // For holonomic drivetrains, you must include "front" and "back" for the motor names
       mik::motor(PORT4, false, green_18_1, "left middle motor"),
   }),
   // Right drivetrain motors
   mik::motor_group({
       mik::motor(PORT6, true, blue_6_1, "right front motor"),
       mik::motor(PORT7, false, green_18_1, "right middle motor"),
       mik::motor(PORT8, true, blue_6_1, "right back motor"),
   }),
  
   PORT19,  // Inertial sensor port
   360,    // Inertial scale (rotation reading after a full 360° turn)
   false,  // Forces inertial sensor to recalibrate until it is within minimum threshold of 0.05 deg for 1 second
  
   3.25,   // Drivetrain wheel diameter (in). Negative flips direction.
   450,    // Drivetrain RPM. Cartridge * gear ratio, (Ex: 600 * (36/48) = 450).


   PORT12,  // Forward tracker port. PORT0 if unused. Accepts "PORT_A"
   2,      // Forward tracker wheel diameter (in). Negative flips direction. Pushing robot forward at 0° should increase Y
   0,      // Forward tracker center distance (in). Positive = right of center, negative = left.


   PORT11,  // Sideways tracker port. PORT0 if unused. Accepts "PORT_A"
   -2,     // Sideways tracker wheel diameter (in). Negative flips direction. Pushing robot right at 0° should increase X
   0,      // Sideways tracker center distance (in). Positive = behind center, negative = in front.


   // Distance sensors mounted on a face of the robot
   mik::distance_reset({
       mik::distance(
           PORT13,         // Distance sensor port
           rear_sensor,   // "front_sensor", "rear_sensor", "left_sensor", "right_sensor"
           4,             // X offset from tracking center (in). Positive = right of center, negative = left.
           6              // Y offset from tracking center (in). Positive = in front of center, negative = behind.
       ),
       mik::distance(PORT13, left_sensor, -6, 4),
   })
);


// Add your devices in assembly.h then create them here


// continous lift 2x 11W motors
mik::motor_group Assembly::lift_motors({
   mik::motor(PORT2, false, green_18_1, "lift_left"),
   mik::motor(PORT9, true, green_18_1, "lift_right"),
});


// chain bar 2x 5.5W motors
// Note: Assembly class declares this member as "chainbar_motors" (no underscore)
mik::motor_group Assembly::chainbar_motors({
   mik::motor(PORT1, false, green_18_1, "chain_bar_left"),
   mik::motor(PORT10, true, green_18_1, "chain_bar_right"),
});


// clamp piston
mik::piston Assembly::clamp_piston(PORT_A);






// mikLib initialization below, you do not need to edit


Assembly assembly;
Constants constants;
vex::competition Competition;


static void loading_screen(bool stop) {
   static vex::task loading_bar;
  
   if (stop) {
       loading_bar.stop();
       return;
   }
  
   Controller.Screen.setCursor(1, 1);
#ifndef FAST_COMPILE
   Brain.Screen.drawImageFromBuffer((uint8_t*)mikLib_logo, 0, 0, mikLib_logo_size);
#endif


   loading_bar = vex::task([](){
       std::string calibrate = "Calibrating";
#ifndef FAST_COMPILE
       Brain.Screen.setFillColor(mik::loading_text_bg_color.c_str());
       Brain.Screen.setPenColor(mik::loading_text_color.c_str());
#endif
       int count = 0;
       while(1) {
           Brain.Screen.printAt(184, 220, calibrate.c_str());
           Controller.Screen.setCursor(1, 1);
           Controller.Screen.print((calibrate).c_str());
           task::sleep(200);
           calibrate.append(".");
           count++;
           if (count > 4) {
               count = 0;
               calibrate = "Calibrating";
               Brain.Screen.printAt(184, 220, (calibrate + "     ").c_str());
               Controller.Screen.setCursor(1, 1);
               Controller.Screen.print((calibrate + "     ").c_str());
           }
       }
       return 0;
   });
}


static void handle_disconnected_devices() {
#ifndef FAST_COMPILE
   int errors = run_diagnostic();
   if (errors > 0) {
       Controller.rumble(".");
       Controller.Screen.setCursor(1, 1);
       Controller.Screen.print((to_string(errors) + " ERRORS DETECTED").c_str());
       Controller.Screen.setCursor(2, 1);
       Controller.Screen.print("[Config]->[Error Data]");
       task::sleep(500);
   }
#endif
}


static void reset_screens() {
   Brain.Screen.clearScreen();
   Controller.Screen.setCursor(1, 1);
   Controller.Screen.print("                                  ");
   Brain.Screen.setCursor(1,1);
   vex::task::sleep(50);
   Brain.Screen.clearScreen();
   Brain.Screen.setFillColor(vex::color::black);
   Brain.Screen.setPenWidth(1);
   Brain.Screen.setPenColor(vex::color::white);
}


void init(void) {
   // Disable user control during initialization to prevent inputs
   disable_user_control(false);


   // Start loading screen
   loading_screen(false);


   // Setup motors
#ifndef FAST_COMPILE
   motors_scr->init_motors();
#endif


   // Calibrate inertial
   chassis.calibrate_inertial();


   // Stop loading screen
   loading_screen(true);


   // Check disconnected devices
   handle_disconnected_devices();


   // Init brain and controller screen
   reset_screens();
}


static bool user_control_disabled = false;


void disable_user_control(bool stop_all_motors_) {
   user_control_disabled = true;
   if (stop_all_motors_) {
       stop_all_motors(vex::brakeType::hold);
       set_brake_all_motors(vex::brakeType::coast);
       stop_all_motors(vex::brakeType::coast);
   }
}


void enable_user_control(void) {
   user_control_disabled = false;
}


bool control_disabled(void) {
   if (Competition.isDriverControl() && (Competition.isFieldControl() || Competition.isCompetitionSwitch()) && user_control_disabled) {
       auton_scr->disable_controller_overlay();
       return false;
   };
   return user_control_disabled;
}


void stop_all_motors(vex::brakeType mode) {
   for (auto motor : mik::motor_registry()) {
       motor->stop(mode);
   }
}


void set_brake_all_motors(vex::brakeType mode) { 
   for (auto motor : mik::motor_registry()) {
       motor->setBrake(mode);
   }
}





