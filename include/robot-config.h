using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern motor_group Tenaza;
extern motor ColitaArriba;
extern motor ColitaAbajo;

extern sonar RangeFinderG;
 
extern limit LimitColita;
extern limit LimitTenaza;

extern gyro TurnGyroSmart;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );