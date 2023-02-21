#include "main.h"

pros::Motor& leftMotor = chassis.left_motors[1];
pros::Motor& rightMotor = chassis.right_motors[1];

pros::ADIDigitalIn slingshotLimit('B');

pros::ADIDigitalOut pto_intake_piston('H');
pros::ADIDigitalOut slingshot('G');
pros::ADIDigitalOut intakePivot('C');
pros::ADIDigitalOut bandReleaseRight('A');
pros::ADIDigitalOut bandReleaseLeft('D');


bool pto_intake_enabled = false;

void ptoOn(){
  pto_intake_piston.set_value(false);
}


void pto_intake(bool toggle) {
  pto_intake_enabled = toggle;
  chassis.pto_toggle({chassis.left_motors[3], chassis.right_motors[3]}, toggle);
  pto_intake_piston.set_value(!toggle);
  if (toggle) {
    chassis.left_motors[3].set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    chassis.right_motors[3].set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
}


void intakeSpeed(int input) {
  if (!pto_intake_enabled) return;
  chassis.left_motors[3] = -input;
  chassis.right_motors[3] = -input;
}

void intakeSpeedAuto(int input){
  chassis.left_motors[3] = -input;
  chassis.right_motors[3] = -input;
}

void intakeLift(){
    intakePivot.set_value(true);
}

void intakeLower(){
    intakePivot.set_value(false);
}

bool first = false;
bool dominic = false;

void lockRelease(){
  dominic = false;
  first = true;
  slingshot.set_value(false);
}

int speed = 0;

void setSpeed(int input){
    speed = input;
}


void slingshotShoot(void* p){
    while(true){

    if(!slingshotLimit.get_value() && dominic == false && first == true){
      pros::delay(100);
      intakeSpeed(-127);
    }
    

    else if(slingshotLimit.get_value() && dominic == false && first == true){
      pros::delay(100);
      dominic = true;
      slingshot.set_value(true);
      
    }
    else if(dominic == true || first == false){
      intakeSpeed(speed);
      pros::delay(10);
    }
    
    pros::delay(10);
    
    }
}

bool slingshotSet = false;

int button_lock = 0;
bool shoot = false;

void setSlingshot(){

    if (master.get_digital(DIGITAL_DOWN) && button_lock == 0) {
    pto_intake(!pto_intake_enabled);
    button_lock = 1;
  } else if (!master.get_digital(DIGITAL_DOWN)) {
    button_lock = 0;
  }

    if(slingshotLimit.get_value()){
        slingshotSet = true;
    }
    if(slingshotSet == true && !master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
        intakeSpeed(0);
        slingshot.set_value(true);
    }
    if(slingshotSet == false && !master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        intakeSpeed(-127);
    }
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        slingshot.set_value(false);
        slingshotSet = false;
    }
}


void intakeControl() {

  if (master.get_digital(DIGITAL_DOWN) && button_lock == 0) {
    pto_intake(!pto_intake_enabled);
    button_lock = 1;
  } else if (!master.get_digital(DIGITAL_DOWN)) {
    button_lock = 0;
  }

  if (master.get_digital(DIGITAL_R1)){
    intakeSpeed(127);
  }
  if (master.get_digital(DIGITAL_R2)){
    intakeSpeed(100);
  }
    

}

bool intakeLiftBool = false;

void intakeLiftDriver(){
  if(master.get_digital_new_press(DIGITAL_Y)){
        intakeLiftBool = !intakeLiftBool;
        
        intakePivot.set_value(intakeLiftBool);
  }
}

void bandRelease(){
  bandReleaseRight.set_value(true);
  bandReleaseLeft.set_value(true);
}

void bandReleaseControl(){
  if(master.get_digital(DIGITAL_B)) {
    bandRelease();
  }
}

void inertialValue(void* p){
  while(true){
    printf("Gyro: %f   Gyro Target: %f   --   Left: %f   Left Target: %f   --   Right: %f   Right Target: %f\n", chassis.get_gyro(), chassis.turnPID.get_target(), chassis.left_sensor() / chassis.get_tick_per_inch(), chassis.leftPID.get_target(), chassis.right_sensor() / chassis.get_tick_per_inch(), chassis.rightPID.get_target());
    pros::delay(10);
  }
}

 