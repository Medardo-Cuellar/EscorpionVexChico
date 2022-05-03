/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

void LimitSwitchTenaza()
{
Tenaza.stop();
}
void LimitSwitchColita()
{
  ColitaAbajo.stop();
  ColitaArriba.stop();
}
void LimiTenaza(int spd)
{
  int a=0;
  while(a==0)
  {
    Tenaza.spin(reverse, spd, pct);
    if (LimitTenaza.pressing()==true)
    {
      Tenaza.rotateFor(forward, 35, degrees);
      Tenaza.stop(hold);
      a=1;
    }
  }
}
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // .......................................................................... 
    // Drives robot backwards 1.15 meters at the default 50% velocity
  //  Tenaza.spinFor(reverse, 100, degrees);
  
  LimiTenaza(60);

  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(forward, 40, inches);
  Drivetrain.stop();

  Drivetrain.setDriveVelocity(50, percent);
  Drivetrain.driveFor(forward, 3, inches);
  wait(1, seconds);

  Drivetrain.setDriveVelocity(90, percent);
  Drivetrain.driveFor(reverse, 47, inches);
  wait(1, seconds);

  Drivetrain.setTurnVelocity(25, percent);
  Drivetrain.turnFor(right, 100, degrees);
  wait(1, seconds);

  // Turns the robot to the left at 25% velocity
  //Drivetrain.turnFor(left, 90, degrees);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
// Deadband stops the motors when Axis values are close to zero.
  int deadband = 5;
  int dir = 0;
  int vel = 0;

  LeftDriveSmart.setStopping(hold);
  RightDriveSmart.setStopping(hold);
  Tenaza.setStopping(hold);
  ColitaArriba.setStopping(hold);
  ColitaAbajo.setStopping(hold);
  
  while (true) 
  {
    if(Controller1.ButtonA.pressing())
    {
      while(Controller1.ButtonA.pressing())
      {
          vex::task::sleep(150);
      }
      dir++;
      Brain.Screen.printAt(1,80,"%d",dir);
    }
    else if (dir==2)
    {
        dir=0;
    }

    
    if(Controller1.ButtonB.pressing())
    {
      while(Controller1.ButtonB.pressing())
      {
          vex::task::sleep(150);
      }
      vel++;
      Brain.Screen.printAt(1,80,"%d",vel);
    }
    else if (vel==2)
    {
        vel=0;
    }
    int leftMotorSpeed;
    int rightMotorSpeed;    

    if(vel==0)
    {
    // Get the velocity percentage of the left motor. (Axis3 + Axis4).
      leftMotorSpeed =  Controller1.Axis3.position() + Controller1.Axis4.position();
          // Get the velocity percentage of the right motor. (Axis3 - Axis4)
      rightMotorSpeed = Controller1.Axis3.position() - Controller1.Axis4.position(); 
    }
    else if(vel==1)
    {
      leftMotorSpeed =  (Controller1.Axis3.position() + Controller1.Axis4.position())/3;
      rightMotorSpeed = (Controller1.Axis3.position() - Controller1.Axis4.position())/3; 
    }
    // set speed on arm and claw

    int TenazaSpeed = 90;
    int ColitaSpeed = 50;

    Tenaza.setVelocity(TenazaSpeed, percent);
    ColitaArriba.setVelocity(ColitaSpeed, percent);
    ColitaAbajo.setVelocity(ColitaSpeed, percent);

    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      LeftDriveSmart.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      LeftDriveSmart.setVelocity(leftMotorSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      RightDriveSmart.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      RightDriveSmart.setVelocity(rightMotorSpeed, percent);
    }

    if(dir==1)
    {
      // Spin both motors in the forward direction.
      LeftDriveSmart.spin(forward);
      RightDriveSmart.spin(forward);  
    }
    else if(dir==0)
    {
      // Spin both motors in the forward direction.
      LeftDriveSmart.spin(reverse);
      RightDriveSmart.spin(reverse);  
    }
    //control de tenaza
      if (Controller1.ButtonR2.pressing()){
         Tenaza.spin(forward);
      }
      else if (Controller1.ButtonR1.pressing()){
          Tenaza.spin(reverse);
      }
      else {
        Tenaza.stop();
      }

      //control de Colita
      if (Controller1.ButtonL1.pressing()){
          ColitaArriba.spin(forward);
          ColitaAbajo.spin(forward);
      }
      else if(Controller1.ButtonL2.pressing()){
          ColitaArriba.spin(reverse);
          ColitaAbajo.spin(reverse);
      }
      else {
          ColitaArriba.stop();
          ColitaAbajo.stop();
      }
    wait(25, msec);
  }

}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
