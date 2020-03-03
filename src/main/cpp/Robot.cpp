#include "Robot.h"

#define StraightShot
// #define SideShot

//joystick creation
frc::Joystick *lonelyStick;
frc::JoystickButton *nuke;       //button 4
frc::JoystickButton *oneSpin;    //button 6
frc::JoystickButton *lessSpeed;  //button 5
frc::JoystickButton *moreSpeed;  //button 3
frc::JoystickButton *fullCheech; //button 2
frc::JoystickButton *putItIn;    //button 1

//tank drive creation
frc::DifferentialDrive *brit;

//controller creation
frc::XboxController *neighborlyInputDevice;

//brit motors
rev::CANSparkMax driveboi1(7, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi2(10, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi3(13, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi4(2, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi5(8, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi6(9, rev::CANSparkMax::MotorType::kBrushless);

//brit motor groups
frc::SpeedControllerGroup speedyboiL(driveboi1, driveboi2, driveboi3);
frc::SpeedControllerGroup speedyboiR(driveboi4, driveboi5, driveboi6);

//winch motor creation
rev::CANSparkMax whench(12, rev::CANSparkMax::MotorType::kBrushless);
//climber motor creation
rev::CANSparkMax spoodermoon(11, rev::CANSparkMax::MotorType::kBrushless);
//mike whipper motor creation
ctre::phoenix::motorcontrol::can::VictorSPX whippedCheese = {25};
//mike whipper up/down solenoid
frc::Solenoid viagra(3);
//intake motor creation
rev::CANSparkMax simp(1, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax egirl(3, rev::CANSparkMax::MotorType::kBrushless);

//limit switch move thing
ctre::phoenix::motorcontrol::can::VictorSPX heli = {26};
int x;

//Encoder creation
rev::CANEncoder spinReader1 = driveboi1.GetEncoder();
rev::CANEncoder spinReader2 = driveboi2.GetEncoder();
rev::CANEncoder spinReader3 = driveboi3.GetEncoder();
rev::CANEncoder spinReader4 = driveboi4.GetEncoder();
rev::CANEncoder spinReader5 = driveboi5.GetEncoder();
rev::CANEncoder spinReader6 = driveboi6.GetEncoder();
//winch encoder creation
rev::CANEncoder pimp = whench.GetEncoder();
//climber encoder creation
rev::CANEncoder gwen = spoodermoon.GetEncoder();

//camera creation
cs::UsbCamera fbi;
cs::UsbCamera cia;

//ultrasonic range sensor creation
frc::AnalogInput batman(0); // 230 - 630 is usable range
//ultrsonic variable
double distance;

//speed var
double speed;
//auton steps variable thing
enum Auton
{
  forward1 = 1,
  dump = 2,
  back1 = 3,
  turn1 = 4,
  forward2 = 5,
  back2 = 6,
  turn2 = 7,
  forward3 = 8,
  null = 9
  /*forwardfromside = 10 (for the UltraSonic Side Shot)
  turnsideshot = 11
*/
};
Auton step;

//sonlenoid creation
frc::Solenoid peerPressure1(0);
frc::Solenoid peerPressure2(1);
//dump intake
frc::Solenoid roboMyRio(2);

//compressor creation
frc::Compressor bonusPressure(0);

//limit switch creation
frc::DigitalInput stopIt(9);

//revolution var
int forwardBackwardDistance = 46; //23 is about 5 ft
int turnDistance = 29;            //25 is about 360 degrees on shop floors, 29 is about 360 on carpet

//toggle variable for intake things
int toggle = 1;

//Dead Zone Variables
double lonelyY;
double lonelyTwist;
double notFarEnough;

//intake stop var
int estop = 1;

<<<<<<< HEAD
== == == =
             //encoder variables
    double forwardBackward;
double turn;

>>>>>>> parent of 819514b... turn button
void Robot::RobotInit()
{
  //m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  //m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  //frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //setting up camera
  fbi = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
  fbi.SetVideoMode(cs::VideoMode::PixelFormat::kYUYV, 320, 240, 10);
  cia = frc::CameraServer::GetInstance()->StartAutomaticCapture(1);
  cia.SetVideoMode(cs::VideoMode::PixelFormat::kYUYV, 320, 240, 10);

  //setting up controller
  neighborlyInputDevice = new frc::XboxController(1);

  //setting up Joystick
  lonelyStick = new frc::Joystick(0);
  nuke = new frc::JoystickButton(lonelyStick, 4);
  oneSpin = new frc::JoystickButton(lonelyStick, 6);
  fullCheech = new frc::JoystickButton(lonelyStick, 2);
  lessSpeed = new frc::JoystickButton(lonelyStick, 5);
  moreSpeed = new frc::JoystickButton(lonelyStick, 3);
  putItIn = new frc::JoystickButton(lonelyStick, 1);

  //setting up drivetrain
  brit = new frc::DifferentialDrive(speedyboiL, speedyboiR);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
}
/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit()
{
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  /*if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } 
  else {
    // Default Auto goes here
  }*/

  step = forward1;
  driveboi2.Follow(driveboi1, /*invert*/ false);
  driveboi4.Follow(driveboi5, /*invert*/ false);
  driveboi3.Follow(driveboi1, /*invert*/ false);
  driveboi6.Follow(driveboi5, /*invert*/ false);

  //limit switch moving thingy
  if (1 == 1)
  {
    heli.Set(ControlMode::PercentOutput, -1);
    Wait(.09);
    heli.Set(ControlMode::PercentOutput, 0);
    x = 1;
  }
}

void Robot::AutonomousPeriodic()
{

  double forwardBackward = spinReader1.GetPosition() - spinReader3.GetPosition();
  double turn = spinReader1.GetPosition() + spinReader3.GetPosition();
// if (m_autoSelected == kAutoNameCustom) {
//   // Custom Auto goes here
// }
// else {
//   // Default Auto goes here
// }

//Straight Shot (Best Option) (Not Tested)
#ifdef StraightShot
  switch (step)
  {
  case forward1:
  {
    if (batman.GetValue() < 95) //230 - 630 usable range
    {
      Robot::Forwards();
    }
    else
    {
      ZeroMotors();
      step = dump;
    }
    break;
  }
  case dump:
  {
    roboMyRio.Set(true);
    Wait(.5);
    roboMyRio.Set(false);
    step = back1;
    break;
  }
  case back1:
  {
    if (forwardBackward < 92)
    {
      Robot::Backwards();
    }
    else
    {
      ZeroMotors();
      step = turn1;
    }
    break;
  }
  case turn1:
  {
    if (turn < 14.5)
    {
      Robot::Clock();
    }
    else
    {
      ZeroMotors();
      step = forward2;
    }
    break;
  }
  case forward2:
  {
    if (batman.GetValue() < 95)
    {
      Robot::Forwards();
    }
    else
    {
      ZeroMotors();
      step = back2;
    }
    break;
  }
  case back2:
  {
    if (forwardBackward < 4.6)
    {
      Robot::Backwards();
    }
    else
    {
      ZeroMotors();
      step = turn2;
    }
    break;
  }
  case turn2:
  {
    if (turn < 14.5)
    {
      Robot::Clock();
    }
    else
    {
      ZeroMotors();
      step = forward3;
    }
    break;
  }
  case forward3:
  {
    if (forwardBackward < 198.49)
    {
      Robot::Forwards();
    }
    else
    {
      ZeroMotors();
      step = null;
    }
    break;
  }
  default:
    break;
  }
#endif

  //UltraSonic Side Shot (2nd Best Option) (Not Tested)
#ifdef SideShot
  switch (step)
  {
  case forwardfromside:
  {
    if (forwardBackward < 92)
    {
      Robot::Forwards();
    }
    else
    {
      ZeroMotors();
      step = turnsideshot;
    }
    break;
  }
  case turnsideshot:
  {
    if (turn < 14.5)
    {
      Robot::Clock();
    }
    else
    {
      ZeroMotors();
      step = forward1;
    }
  }
  case forward1:
  {
    if (batman.GetValue() < 95) //230 - 630 usable range
    {
      Robot::Forwards();
    }
    else
    {
      ZeroMotors();
      step = dump;
    }
    break;
  }
  case dump:
  {
    roboMyRio.Set(true);
    Wait(.5);
    roboMyRio.Set(false);
    step = back1;
    break;
  }
  case back1:
  {
    if (forwardBackward < 92)
    {
      Robot::Backwards();
    }
    else
    {
      ZeroMotors();
      step = turn1;
    }
    break;
  }
  case turn1:
  {
    if (turn < 14.5)
    {
      Robot::Clock();
    }
    else
    {
      ZeroMotors();
      step = forward2;
    }
    break;
  }
  case forward2:
  {
    if (batman.GetValue() < 95)
    {
      Robot::Forwards();
    }
    else
    {
      ZeroMotors();
      step = back2;
    }
    break;
  }
  case back2:
  {
    if (forwardBackward < 4.6)
    {
      Robot::Backwards();
    }
    else
    {
      ZeroMotors();
      step = turn2;
    }
    break;
  }
  case turn2:
  {
    if (turn < 14.5)
    {
      Robot::Clock();
    }
    else
    {
      ZeroMotors();
      step = forward3;
    }
    break;
  }
  case forward3:
  {
    if (forwardBackward < 198.49)
    {
      Robot::Forwards();
    }
    else
    {
      ZeroMotors();
      step = null;
    }
    break;
  }
  default:
    break;
  }
#endif
}

void Robot::TeleopInit()
{
  //limit switch moving thingy but the other way
  if (x == 1)
  {
    heli.Set(ControlMode::PercentOutput, 1);
    Wait(.075);
    heli.Set(ControlMode::PercentOutput, 0);
    x = 2;
  }
}

void Robot::TeleopPeriodic()
{
  //limit switch move button
  if (neighborlyInputDevice->GetStartButton())
  {
    heli.Set(ControlMode::PercentOutput, .1);
  }
  else
  {
    heli.Set(ControlMode::PercentOutput, 0);
  }

  //42 counts per rev. on neo
  if (spinReader1.GetVelocity() == 0)
    spinReader1.SetPosition(0);
  if (spinReader2.GetVelocity() == 0)
    spinReader2.SetPosition(0);
  if (spinReader3.GetVelocity() == 0)
    spinReader3.SetPosition(0);
  if (spinReader4.GetVelocity() == 0)
    spinReader4.SetPosition(0);
  if (spinReader5.GetVelocity() == 0)
    spinReader5.SetPosition(0);
  if (spinReader6.GetVelocity() == 0)
    spinReader6.SetPosition(0);

  //Read Encoder
  frc::SmartDashboard::PutNumber("Encoder1 Position", spinReader1.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder2 Position", spinReader2.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder3 Position", spinReader3.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder4 Position", spinReader4.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder5 Position", spinReader5.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder6 Position", spinReader6.GetPosition());
  frc::SmartDashboard::PutNumber("climber position", -gwen.GetPosition());
  //read sensor
  double distance = batman.GetValue() * 0.393701; //multiplying by 0.393701 converts the sonar value to inches (hopefully)
  frc::SmartDashboard::PutNumber("Range Sensor 1", distance);

  // Code for deadzones on joystick
  notFarEnough = .05; /*todo: Adjust to driver's needs*/
  if (-lonelyStick->GetY() < notFarEnough || -lonelyStick->GetY() > -notFarEnough)
  {
    lonelyY = lonelyStick->GetY();
  }
  if (lonelyStick->GetTwist() < notFarEnough || lonelyStick->GetTwist() > -notFarEnough)
  {
    lonelyTwist = -lonelyStick->GetTwist();
  }

  //making the compressor compress
  bonusPressure.SetClosedLoopControl(true);

  //gearbox shifting code
  peerPressure2.Set(lessSpeed->Get());
  peerPressure1.Set(moreSpeed->Get());

  //pneumatic actuator
  if (neighborlyInputDevice->GetXButton())
  {
    roboMyRio.Set(true);
    Robot::Wait(.5);
    roboMyRio.Set(false);
  }

  //mike whipper and intake code
  if (neighborlyInputDevice->GetAButtonReleased())
  {
    toggle = -toggle;
  }

  if (neighborlyInputDevice->GetBackButtonPressed())
  {
    estop = -estop;
  }
  else if (estop == 1)
  {
    simp.Set(0);
  }
  else if (estop == -1)
  {
    simp.Set(-1);
  }

  if (neighborlyInputDevice->GetYButton())
  {
    viagra.Set(false);
    simp.Set(1);
    egirl.Set(-1);
  }
  else if (toggle == 1)
  {
    viagra.Set(false);
    simp.Set(0);
    egirl.Set(0);
    whippedCheese.Set(ControlMode::PercentOutput, 0); //should be 0 just testing
  }
  else if (toggle == -1)
  {
    viagra.Set(true);
    simp.Set(-1);
    egirl.Set(1);
    whippedCheese.Set(ControlMode::PercentOutput, 1); //should be .1 just testing
  }

  //winch code
  if (neighborlyInputDevice->GetBButton())
  {
    whench.Set(1);
  }
  else
  {
    whench.Set(0);
  }

  //climber code
  if (neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand) > 0)
  {
    spoodermoon.Set(-neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand) * .2);
  }
  else if (neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) > 0)
  {
    spoodermoon.Set(neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) * .2);
  }
  else
  {
    spoodermoon.Set(0);
  }

  //Bumber to preset climbing positions (63 in and all the way down)
  if (neighborlyInputDevice->GetBumper(frc::GenericHID::JoystickHand::kRightHand) && -gwen.GetPosition() < 75)
  {
    spoodermoon.Set(-.3);
  }
  else if (neighborlyInputDevice->GetBumper(frc::GenericHID::JoystickHand::kLeftHand) && -gwen.GetPosition() > 0)
  {
    spoodermoon.Set(.2);
  }

  //90 Degrees turn code (Not Tested)
  if (fullCheech->Get() && turn > -10)
  {
    Robot::CounterClock();
  }
  else if (putItIn->Get() && turn < 10)
  {
    Robot::Clock();
  }
  else
  {
    ZeroMotors();
  }

  speed = .8;

  brit->ArcadeDrive(lonelyY * speed, lonelyTwist * speed);
}

void Robot::TestPeriodic() {}

void Robot::ZeroMotors()
{
  driveboi1.Set(0);
  driveboi3.Set(0);
  spinReader1.SetPosition(0);
  spinReader2.SetPosition(0);
  spinReader3.SetPosition(0);
  spinReader4.SetPosition(0);
  spinReader5.SetPosition(0);
  spinReader6.SetPosition(0);
}

void Robot::Forwards()
{
  driveboi1.Set(.5);
  driveboi5.Set(-.5);
}
void Robot::Backwards()
{
  driveboi1.Set(-.5);
  driveboi5.Set(.5);
}
void Robot::Clock()
{
  driveboi1.Set(.5);
  driveboi5.Set(.5);
}
void Robot::CounterClock()
{
  driveboi1.Set(-.5);
  driveboi5.Set(-.5);
}
void Robot::Wait(double seconds)
{
  clock_t endwait;
  endwait = clock() + seconds * CLOCKS_PER_SEC;
  while (clock() < endwait)
  {
  }
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif