#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);//11,0,20,0
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

void elimsLeft(){
  pto_intake(true);
  //lockRelease();
  //pros::delay(3000);
  setSpeed(50);
  chassis.set_drive_pid(-2.5,DRIVE_SPEED,true);
  chassis.wait_drive();
  pros::delay(300);
  chassis.set_drive_pid(6.5,DRIVE_SPEED,true);
  chassis.wait_until(2);
  setSpeed(127);
  chassis.wait_drive();
  pros::delay(1000);
  chassis.set_turn_pid(-51,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-13,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(23,TURN_SPEED);
  chassis.wait_drive();
  intakeLift();
  chassis.set_drive_pid(14,DRIVE_SPEED,true);
  chassis.wait_drive();
  pros::delay(300);
  lockRelease();
  pros::delay(1400);
  intakeLower();
  pros::delay(3000);
  lockRelease();
  pros::delay(100);
  intakeLift();
  chassis.set_drive_pid(-11,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(86,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(24,DRIVE_SPEED,true);
  chassis.wait_drive();
  intakeLower();
  pros::delay(2000);
  chassis.set_turn_pid(12,TURN_SPEED);
  chassis.wait_drive();
  pros::delay(200);
  lockRelease();
  pros::delay(200);
  setSpeed(0);
  bandRelease();


}

void elimsRight(){
  pto_intake(true);
  //lockRelease();
  //pros::delay(3000);
  setSpeed(127);
  chassis.set_drive_pid(25,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_drive_pid(-10,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-28,TURN_SPEED);
  chassis.wait_drive();

  pros::delay(1000);
  lockRelease();
  pros::delay(1500);

  chassis.set_turn_pid(-84,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(60,40,true);
  chassis.wait_drive();
  pros::delay(700);
  chassis.set_turn_pid(3,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-5,DRIVE_SPEED,true);
  chassis.wait_drive();

  pros::delay(300);
  lockRelease();
  pros::delay(200);

  chassis.set_turn_pid(-87,TURN_SPEED);
  chassis.wait_drive();
  bandRelease();
  chassis.set_drive_pid(-79,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-36,TURN_SPEED);
  chassis.wait_drive();
  setSpeed(50);
  chassis.set_drive_pid(-7,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_drive_pid(5,DRIVE_SPEED,true);
  chassis.wait_drive();



}



void WP(){
  pto_intake(true);
  //lockRelease();
  //pros::delay(3000);
  setSpeed(60);
  chassis.set_drive_pid(-2.5,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_drive_pid(5,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(40,TURN_SPEED);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(26,127,true);
  chassis.wait_drive();
  chassis.set_drive_pid(-3,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-20,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(4,DRIVE_SPEED,true);
  chassis.wait_drive();

  pros::delay(300);
  lockRelease();
  pros::delay(200);

  chassis.set_drive_pid(-4,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(43,TURN_SPEED);
  chassis.wait_drive();
  pros::delay(600);
  chassis.set_drive_pid(54,40,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-46,70);
  chassis.wait_drive();
  chassis.set_drive_pid(-11,DRIVE_SPEED);
  chassis.wait_drive();

  pros::delay(200);
  lockRelease();
  pros::delay(200);

  chassis.set_drive_pid(18,DRIVE_SPEED,true);
  chassis.wait_drive();
  bandRelease();
  chassis.set_turn_pid(43,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(75,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-90,TURN_SPEED);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(-15,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_drive_pid(5,DRIVE_SPEED,true);
  chassis.wait_drive();



}

void skills(){
  /*chassis.initialize();
  pros::delay(5000);
  pto_intake(true);
  lockRelease();
  pros::delay(3000);*/
  pto_intake(true);
  setSpeed(0);
  //tune
  chassis.set_drive_pid(-2.5,DRIVE_SPEED,true);
  chassis.wait_drive();
  setSpeed(100);
  pros::delay(300);
  setSpeed(0);
  chassis.set_drive_pid(6,DRIVE_SPEED,true);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_turn_pid(-58, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(16,DRIVE_SPEED,true);
  chassis.wait_drive();
  setSpeed(100);
  pros::delay(300);
  setSpeed(0);
  chassis.set_drive_pid(-8.5,DRIVE_SPEED,true);
  chassis.wait_drive();
  setSpeed(127);

  chassis.set_turn_pid(0, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(69,80,true);
  chassis.wait_drive();
  chassis.set_turn_pid(6, 60);
  chassis.wait_drive();


  pros::delay(300);
  lockRelease();
  pros::delay(200);

  chassis.set_turn_pid(0, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(-57,80,true);
  chassis.wait_drive();
  chassis.set_turn_pid(42, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(77,50,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-45, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(12,DRIVE_SPEED,true);
  chassis.wait_drive();

  pros::delay(300);
  lockRelease();
  pros::delay(200);

  chassis.set_drive_pid(-13,DRIVE_SPEED,true);
  chassis.wait_drive();

  chassis.set_turn_pid(40, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(32,DRIVE_SPEED,true);
  chassis.wait_drive();
  pros::delay(700);
  chassis.set_drive_pid(36,40,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(45,80,true);
  chassis.wait_drive();

  pros::delay(300);
  lockRelease();
  pros::delay(200);

  chassis.set_drive_pid(-57,80,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-180, 60);
  chassis.wait_drive();

  setSpeed(0);
  chassis.set_drive_pid(-23,70,true);
  chassis.wait_drive();
  setSpeed(100);
  pros::delay(300);
  setSpeed(0);
  chassis.set_drive_pid(23,DRIVE_SPEED,true);
  chassis.wait_until(10);
  setSpeed(127);
  chassis.wait_drive();
  pros::delay(800);
  chassis.set_drive_pid(26,40,true);
  chassis.wait_drive();
  chassis.set_drive_pid(-12,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(-35,70,true);
  chassis.wait_drive();
  setSpeed(100);
  pros::delay(300);
  setSpeed(0);
  chassis.set_drive_pid(7,DRIVE_SPEED,true);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_turn_pid(-180, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(60,80,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-172, 60);
  chassis.wait_drive();

  pros::delay(300);
  lockRelease();
  pros::delay(1000);

  chassis.set_turn_pid(-180, 60);
  chassis.set_drive_pid(-61,80,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-137, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(77,50,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-225, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(8,DRIVE_SPEED,true);
  chassis.wait_drive();

  pros::delay(300);
  lockRelease();
  pros::delay(200);

  chassis.set_drive_pid(-30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-310, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(-79,DRIVE_SPEED,true);
  chassis.wait_drive();
  
  endgameShoot();
  pros::delay(1000);
  endgameShoot2();
  pros::delay(500);
  endgameShoot();

  
}

void testMovements(){
  pto_intake(true);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 60);
  chassis.wait_drive();
  setSpeed(127);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, 60);
  chassis.wait_drive();
  setSpeed(60);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, 60);
  chassis.wait_drive();
  setSpeed(0);
  chassis.set_drive_pid(30,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(360, 60);
  chassis.wait_drive();
  
}

/*void skills(){
  pto_intake(true);
  //lockRelease();
  //pros::delay(3000);
  setSpeed(100);
  //tune
  chassis.set_drive_pid(-2.5,DRIVE_SPEED,true);
  chassis.wait_drive();
  pros::delay(800);
  chassis.set_drive_pid(6.5,DRIVE_SPEED,true);
  chassis.wait_until(2);
  setSpeed(127);
  chassis.wait_drive();
  pros::delay(1000);
  chassis.set_turn_pid(-51,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-13,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(23,TURN_SPEED);
  chassis.wait_drive();
  intakeLift();
  chassis.set_drive_pid(14,DRIVE_SPEED,true);
  chassis.wait_drive();
  pros::delay(300);
  lockRelease();
  pros::delay(1400);
  intakeLower();
  pros::delay(5000);
  lockRelease();
  pros::delay(100);
  intakeLift();
  chassis.set_drive_pid(-11,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(86,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(24,DRIVE_SPEED,true);
  chassis.wait_drive();
  intakeLower();
  pros::delay(4000);
  chassis.set_turn_pid(14,TURN_SPEED);
  chassis.wait_drive();
  //chassis.set_drive_pid(5,DRIVE_SPEED,true);
  //chassis.wait_drive();

  pros::delay(200);
  lockRelease();
  pros::delay(200);
  bandRelease();

  //chassis.set_drive_pid(-5,DRIVE_SPEED,true);
  //chassis.wait_drive();
  chassis.set_turn_pid(80,TURN_SPEED);
  chassis.wait_drive();
  pros::delay(800);
  //tune
  chassis.set_drive_pid(100,40,true);
  chassis.wait_drive();
  //tune
  chassis.set_turn_pid(207,TURN_SPEED);
  chassis.wait_drive();
  //tune
  chassis.set_drive_pid(36,DRIVE_SPEED,true);
  chassis.wait_drive();

  pros::delay(200);
  lockRelease();
  pros::delay(200);

  chassis.set_drive_pid(-60,DRIVE_SPEED,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-90,TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-8,DRIVE_SPEED,true);
  chassis.wait_drive();

  endgameShoot();
  pros::delay(1000);
  endgameShoot2();
  pros::delay(1000);
  endgameShoot();
  pros::delay(1000);
  endgameShoot2();
  pros::delay(1000);
  endgameShoot();
  pros::delay(1000);
  endgameShoot2();
  pros::delay(1000);
  endgameShoot();
  pros::delay(1000);
  endgameShoot2();
  

}*/