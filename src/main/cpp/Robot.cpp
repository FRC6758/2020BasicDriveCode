/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "cscore.h"
#include "Robot.h"
#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>
#include <frc/drive/differentialDrive.h>
#include "rev/CANSparkMax.h"
#include <iostream>
#include <frc/SpeedControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <cameraserver/CameraServer.h>
#include <frc/XboxController.h>
#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include <cmath>
#include <frc/Compressor.h>
#include <frc/AnalogInput.h>
#include <frc/DigitalOutput.h>
#include <frc/PWMVictorSPX.h>


//#define Brit

//#define Sounds

//joystick creation
frc::Joystick *lonelyStick;
frc::JoystickButton *nuke;       //button 4
frc::JoystickButton *oneSpin;    //button 6
frc::JoystickButton *lessSpeed;  //button 5
frc::JoystickButton *moreSpeed;  //button 3
frc::JoystickButton *fullCheech; //button 2
frc::JoystickButton *putItIn;    //button 1
#ifdef Sounds
frc::JoystickButton *sound1; //button 7
frc::JoystickButton *sound2; //button 8
frc::JoystickButton *sound3; //button 9
frc::JoystickButton *sound4; //button 11
frc::JoystickButton *sound5; //button 12
#endif

//digital input creation
frc::DigitalOutput playSound1(1);

//controller creation
frc::XboxController *soundController;

//tank drive creation
frc::DifferentialDrive *brit;

//brit motors
#ifdef Brit
rev::CANSparkMax driveboi1(7, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi2(10, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi3(13, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi4(2, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi5(8, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi6(9, rev::CANSparkMax::MotorType::kBrushless);

//brit motor groups
frc::SpeedControllerGroup speedyboiL(driveboi1, driveboi2, driveboi3);
frc::SpeedControllerGroup speedyboiR(driveboi4, driveboi5, driveboi6);
#endif

#ifndef Brit
//axel motors
rev::CANSparkMax driveboi1(4, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi2(6, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi3(1, rev::CANSparkMax::MotorType::kBrushless);
rev::CANSparkMax driveboi4(3, rev::CANSparkMax::MotorType::kBrushless);

//axel motor croups
frc::SpeedControllerGroup speedyboiL(driveboi1, driveboi2);
frc::SpeedControllerGroup speedyboiR(driveboi3, driveboi4);
#endif

//Encoder creation
rev::CANEncoder spinReader1 = driveboi1.GetEncoder();
rev::CANEncoder spinReader2 = driveboi2.GetEncoder();
rev::CANEncoder spinReader3 = driveboi3.GetEncoder();
rev::CANEncoder spinReader4 = driveboi4.GetEncoder();
#ifdef Brit
rev::CANEncoder spinReader5 = driveboi5.GetEncoder();
rev::CANEncoder spinReader6 = driveboi6.GetEncoder();
#endif

//camera creation
cs::UsbCamera fbi;

//ultrasonic range sensor creation
frc::AnalogInput batman(0);
//ultrsonic variable
double distance = batman.GetValue() * .125; //multiplying by .125 converts the sonar value to inches

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
  forward3 = 8
};
Auton step;

//sonlenoid creation
frc::Solenoid peerPressure1(0);
frc::Solenoid peerPressure2(1);
frc::Solenoid roboMyRio(2);

//compressor creation
frc::Compressor bonusPressure(0);

//limit switch creation
frc::DigitalInput stopIt(4);

//revolution var
int forwardBackwardDistance = 46; //23 is about 5 ft
int turnDistance = 29;            //25 is about 360 degrees on shop floors, 29 is about 360 on carpet

//Dead Zone Variables
double lonelyY;
double lonelyTwist;
double notFarEnough;

void Robot::RobotInit()
{
  //m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  //m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  //frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //setting up camera
  fbi = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
  fbi.SetVideoMode(cs::VideoMode::PixelFormat::kYUYV, 320, 240, 10);

  //setting up controller
  //neighborlyInputDevice = new frc::XboxController(0);

  //setting up Joystick
  lonelyStick = new frc::Joystick(0);
  nuke = new frc::JoystickButton(lonelyStick, 4);
  oneSpin = new frc::JoystickButton(lonelyStick, 6);
  fullCheech = new frc::JoystickButton(lonelyStick, 2);
  lessSpeed = new frc::JoystickButton(lonelyStick, 5);
  moreSpeed = new frc::JoystickButton(lonelyStick, 3);
  putItIn = new frc::JoystickButton(lonelyStick, 1);
#ifdef Sounds
  sound1 = new frc::JoystickButton(lonelyStick, 7);
  sound2 = new frc::JoystickButton(lonelyStick, 8);
  sound3 = new frc::JoystickButton(lonelyStick, 9);
  sound4 = new frc::JoystickButton(lonelyStick, 11);
  sound5 = new frc::JoystickButton(lonelyStick, 12);
#endif

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
}

void Robot::AutonomousPeriodic()
{
  driveboi2.Follow(driveboi1, /*invert*/ false);
  driveboi4.Follow(driveboi3, /*invert*/ false);
#ifdef Brit
  driveboi5.Follow(driveboi1, /*invert*/ false);
  driveboi6.Follow(driveboi3, /*invert*/ false);
#endif

  double forwardBackward = spinReader1.GetPosition() - spinReader3.GetPosition();
  double turn = spinReader1.GetPosition() + spinReader3.GetPosition();
  /*if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } 
  else {
    // Default Auto goes here
  }*/

  switch (step)
  {
  case forward1:
  {
    if (!stopIt.Get())
    {
      driveboi1.Set(.1);
      driveboi3.Set(-.1);
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
    step = back1;
    break;
  }
  case back1:
  {
    if (forwardBackward > -92)
    {
      driveboi1.Set(-.1);
      driveboi3.Set(.1);
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
      driveboi1.Set(.1);
      driveboi3.Set(.1);
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
    if (forwardBackward < 72.578)
    {
      driveboi1.Set(.1);
      driveboi3.Set(-.1);
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
    if (forwardBackward > -4.6)
    {
      driveboi1.Set(-.1);
      driveboi3.Set(.1);
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
      driveboi1.Set(.1);
      driveboi3.Set(.1);
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
      driveboi1.Set(.1);
      driveboi3.Set(-.1);
    }
    else
    {
      ZeroMotors();
      step = dump;
    }
    break;
  }
  default:
    break;
  }
  /*auton idea
        go forward until limit switch hits wall or range gets to very low
        dump balls
        go backward until across the line
        turn tward wall
        go forward until limit switch hits wall or range gets to very low
        back up a little
        turn 90 degrees twards our side
        turn on intake things
        go forward under the trench*/
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic()
{

  //42 counts per rev. on neo
  if (spinReader1.GetVelocity() == 0)
    spinReader1.SetPosition(0);
  if (spinReader2.GetVelocity() == 0)
    spinReader2.SetPosition(0);
  if (spinReader3.GetVelocity() == 0)
    spinReader3.SetPosition(0);
  if (spinReader4.GetVelocity() == 0)
    spinReader4.SetPosition(0);
#ifdef Brit
  if (spinReader5.GetVelocity() == 0)
    spinReader5.SetPosition(0);
  if (spinReader6.GetVelocity() == 0)
    spinReader6.SetPosition(0);
#endif

  //Read Encoder
  frc::SmartDashboard::PutNumber("Encoder1 Position", spinReader1.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder2 Position", spinReader2.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder3 Position", spinReader3.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder4 Position", spinReader4.GetPosition());
#ifdef Brit
  frc::SmartDashboard::PutNumber("Encoder5 Position", spinReader5.GetPosition());
  frc::SmartDashboard::PutNumber("Encoder6 Position", spinReader6.GetPosition());
#endif

  //read sensor
  double distance = batman.GetValue() * .125; //multiplying by .125 converts the sonar value to inches
  frc::SmartDashboard::PutNumber("Range Sensor 1", distance);

  // Code for deadzones on joystick
  notFarEnough = .05; /*todo: Adjust to driver's needs*/
  if (-lonelyStick->GetY() < notFarEnough || -lonelyStick->GetY() > -notFarEnough)
  {
    lonelyY = lonelyStick->GetY();
  }
  if (lonelyStick->GetTwist() < notFarEnough || lonelyStick->GetTwist() > -notFarEnough)
  {
#ifdef Brit
    lonelyTwist = -lonelyStick->GetTwist();
#endif

#ifndef Brit
    lonelyTwist = lonelyStick->GetTwist();
#endif
  }

  //making the compressor compress
  bonusPressure.SetClosedLoopControl(true);

  //gearbox shifting code
  peerPressure2.Set(lessSpeed->Get());
  peerPressure1.Set(moreSpeed->Get());

  //pneumatic actuator
  roboMyRio.Set(putItIn->Get());

  //drive train code
  if (fullCheech->Get())
  {
    speed = 1;
  }
  else
  {
    speed = .4;
  }
  brit->ArcadeDrive(lonelyY * speed, lonelyTwist * speed);

  /*//joystick values to movement in drivetrain
brit->ArcadeDrive ( -lonelyStick->GetY () , lonelyStick->GetTwist () );*/

  //controller values to movement in drivetrain
  //brit->ArcadeDrive ( soundController->GetY ( frc::GenericHID::JoystickHand::kLeftHand ) , soundController->GetX ( frc::GenericHID::JoystickHand::kLeftHand ) );

  //testing to use controller
  /*double testingboi = soundController->GetX(frc::GenericHID::JoystickHand::kLeftHand);
if ( testingboi > 0 ) {
  std::cout << "x axis is goin \n";
}*/
#ifdef Sounds
  /*if (lonelyStick.GetThrottle() == 1)
  {
    if (sound1 && sound2 && sound3)
    {
    }
    if (sound1 && sound2 && sound4)
    {
    }
    if (sound1 && sound2 && sound5)
    {
    }
    if (sound1 && sound2 && sound6)
    {
    }
  }
  if (lonelyStick.GetThrottle() == 0)
  {
  }*/
  if (sound3->Get())
  {
    playSound1.Set(true);
  }
  else
  {
    playSound1.Set(false);
  }
#endif
}

void Robot::TestPeriodic()
{

  /*
//back motors following front motors
//driveboi2.Follow (driveboi1,  false);
//driveboi4.Follow (driveboi3,  false);
//driveboi5.Follow (driveboi1,  false);
//driveboi6.Follow (driveboi3,  false);

//encoder math 
forwardBackward = spinReader1.GetPosition() - spinReader3.GetPosition();
turn = spinReader1.GetPosition() + spinReader3.GetPosition();
forwardBackwardDistance = 46; //23 is about 5 ft
turnDistance = 29; //25 is about 360 degrees on shop floors, 29 is about 360 on carpet

if (oneSpin->Get()) {
  driveboi1.Set(.1);
  driveboi3.Set(-.1);
} else if (nuke->Get()) {
  driveboi1.Set(-.1);
  driveboi3.Set(.1);
} else if (moreSpeed->Get()) {
  driveboi1.Set(-.1);
  driveboi3.Set(-.1);
} else if (lessSpeed->Get()) {
  driveboi1.Set(.1);
  driveboi3.Set(.1);
} else if ( forwardBackward < -2*forwardBackwardDistance || forwardBackward > 2*forwardBackwardDistance || turn < -2*turnDistance || turn > 2*turnDistance ) {
  driveboi1.Set(0);
  driveboi3.Set(0);
  spinReader1.SetPosition(0);
  spinReader2.SetPosition(0);
  spinReader3.SetPosition(0);
  spinReader4.SetPosition(0);
  }


//Motor spins once with Joystick button
//if (spinReader1.GetPosition() < 10) driveboi1.Set(.25);
if (spinReader1.GetPosition() < r) driveboi1.Set(.1);
else if (spinReader1.GetPosition() > r) driveboi1.Set(-.1);
//else if (spinReader1.GetPosition() < 10 ) driveboi1.Set(-1/2*spinReader1.GetPosition()+5);
else driveboi1.Set(0);

//if (spinReader3.GetPosition() > -10) driveboi3.Set(-.25);
if (spinReader3.GetPosition() > -r ) driveboi3.Set(-.1);
else if (spinReader3.GetPosition() < -r) driveboi3.Set(.1);
//else if (spinReader3.GetPosition() > -10 ) driveboi3.Set(1/2*spinReader1.GetPosition()-5);
else driveboi3.Set(0);

motor group = .99^encoder value
motor group = -.99^encoder value
make sure the opposite encoder stuff is the opposite otherwise as it counts up it will keep getting faster/ need two different equations
driveboi1.Set(.99^spinReader1.GetPosition()) for the positive side
*/
}

void Robot::ZeroMotors()
{
  driveboi1.Set(0);
  driveboi3.Set(0);
  spinReader1.SetPosition(0);
  spinReader2.SetPosition(0);
  spinReader3.SetPosition(0);
  spinReader4.SetPosition(0);
#ifdef Brit
  spinReader5.SetPosition(0);
  spinReader6.SetPosition(0);
#endif
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif