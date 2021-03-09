#include "main.h"
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor Left(2);
pros::Motor Right(3);
pros:: Motor Hand(6);
pros::Motor Claw(1);
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 //#include " PreCode/PID.hpp"
 /**
  * Runs the user autonomous code. This function will be started in its own task
  * with the default priority and stack size whenever the robot is enabled via
  * the Field Management System or the VEX Competition Switch in the autonomous
  * mode. Alternatively, this function may be called in initialize or opcontrol
  * for non-competition testing purposes.
  **
   the autonomous task
  * will be stopped. Re-enabling the robot will resstart the task, not re-start it
  * from where it left off.
  */

  void SetDrivePower(int left, int right)
  {

    Left.move(left);
    Right.move(right);
  }
  //Drive Forward, Backwards
  void MoveByEncoderValue(int power, int targetValue)
  {

    Left.set_zero_position(0);
    Right.set_zero_position(0);

    while(abs((Left.get_position() + Right.get_position())/2) < targetValue) //While we are goin to our target unit
    {
      Left.move(power);
      Right.move(power);

      //or
      SetDrivePower(power, power);
    }
    SetDrivePower(0, 0);
  }
  void TurnByEncoderValue(int LeftPower, int RightPower, int TurnAmount, bool TurnRight)
  {
    Left.set_zero_position(0);
    Right.set_zero_position(0);
    if(TurnRight == true)
    {
      while(abs(Left.get_position()) < TurnAmount && abs(Right.get_position()) > -TurnAmount)
      {
        SetDrivePower(LeftPower, RightPower);
      }
    }
    else
    {
      while(abs(Right.get_position()) < TurnAmount && abs(Left.get_position()) > -TurnAmount)
      {
        SetDrivePower(LeftPower, RightPower);
      }
    }
    SetDrivePower(0, 0);
  }

 //Keep keep track absolue position
 //Cons: Values might be consistent
 //Pro: Absolute so you don't have to do extra calculations

 //Reset postion everytime we
 //Advanges: You will go the same amount and not lose position
 //Disadv: No set value, so if arm drifts a tiny bit when moving, it can throw
 pros::Motor LiftM(5);
 void MoveLift(int targetValue, int power)
 {
   LiftM.set_zero_position(0);
   //while encoder does not reach the target
   while(abs(LiftM.get_position()) < targetValue)
   {
     LiftM.move(power);
   }
   LiftM.move(0);
 }
void RedAuton()
{
	//Red Auton Code
}
void BlueAuton()
{
	//Blue Auton Code
}
void Skills()
{
	//Skills code
}
 void autonomous() {

 }


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 void opcontrol() {

     while (true) {
         int left= master.get_analog(ANALOG_LEFT_Y);
         int right=master.get_analog(ANALOG_RIGHT_Y);
         Left.move(left);
         Right.move(right);
         if(master.get_digital(DIGITAL_L1))
         {
             Hand.move(200);
         }
         else if(master.get_digital(DIGITAL_L2))
         {
             Hand.move(-200);
         }
         else{
             Hand.move(0);
         }
         if(master.get_digital(DIGITAL_R1))
         {
             Claw.move(200);
         }
         else if(master.get_digital(DIGITAL_R2))
         {
             Claw.move(-200);
         }
         else{
             Claw.move(0);
         }
     }
 }
