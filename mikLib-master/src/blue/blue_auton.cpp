#include "vex.h"

using namespace vex;
using namespace std;

std::string red_auton(bool calibrate, mik::auto_variation var, bool get_name) {
    chassis_mirror_all_auton_x_pos();
    chassis_mirror_all_auton_y_pos();
    if (get_name) { return "blue right winpoint"; }
    if (calibrate) {
        red_auton(calibrate, var, get_name);
    }
    red_auton(calibrate, var, get_name);

    return "";
}