#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors

limit LimitTenaza = limit(Brain.ThreeWirePort.A);
limit LimitColita = limit(Brain.ThreeWirePort.E);

gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.H);

sonar RangeFinderG = sonar(Brain.ThreeWirePort.G);

controller Controller1 = controller(primary);

motor MotorIzq1 = motor(PORT11, ratio18_1, true);
motor MotorIzq2 = motor(PORT12, ratio18_1, false);
motor MotorIzq3 = motor(PORT13, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(MotorIzq1, MotorIzq2, MotorIzq3);

motor MotorDer1 = motor(PORT14, ratio18_1, false); 
motor MotorDer2 = motor(PORT19, ratio18_1, true); 
motor MotorDer3 = motor(PORT18, ratio18_1, false); 
motor_group RightDriveSmart = motor_group(MotorDer1, MotorDer2, MotorDer3);

drivetrain Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart,TurnGyroSmart, 319.19, 320, 130, mm, 1);

motor Mot_tenL = motor (PORT1, ratio18_1, true);
motor Mot_tenR = motor (PORT2, ratio18_1, false);
motor_group Tenaza = motor_group(Mot_tenL,Mot_tenR);

motor ColitaArriba = motor (PORT3, ratio18_1, true);
motor ColitaAbajo = motor (PORT4, ratio18_1, false);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.startCalibration(1);
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}