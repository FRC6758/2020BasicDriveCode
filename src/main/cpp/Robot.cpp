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
#include "ctre/Phoenix.h"

#define Brit

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
frc::SpeedControllerGroup speedyboiR(driveboi1, driveboi2);
frc::SpeedControllerGroup speedyboiL(driveboi3, driveboi4);
#endif

//winch motor creation
rev::CANSparkMax whench(0, rev::CANSparkMax::MotorType::kBrushless);
//climber motor creation
rev::CANSparkMax spoodermoon(11, rev::CANSparkMax::MotorType::kBrushless);
//mike whipper motor creation
ctre::phoenix::motorcontrol::can::VictorSPX whippedCheese = {25};
//mike whipper up/down solenoid
frc::Solenoid viagra(3);
//intake motor creation
rev::CANSparkMax simp(0, rev::CANSparkMax::MotorType::kBrushless);

//Encoder creation
rev::CANEncoder spinReader1 = driveboi1.GetEncoder();
rev::CANEncoder spinReader2 = driveboi2.GetEncoder();
rev::CANEncoder spinReader3 = driveboi3.GetEncoder();
rev::CANEncoder spinReader4 = driveboi4.GetEncoder();
#ifdef Brit
rev::CANEncoder spinReader5 = driveboi5.GetEncoder();
rev::CANEncoder spinReader6 = driveboi6.GetEncoder();
#endif
//winch encoder creation
rev::CANEncoder pimp = whench.GetEncoder();
//climber encoder creation
rev::CANEncoder gwen = spoodermoon.GetEncoder();

//camera creation
cs::UsbCamera fbi;

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
};
Auton step;

//sonlenoid creation
frc::Solenoid peerPressure1(0);
frc::Solenoid peerPressure2(1);
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

void Robot::RobotInit()
{
  //m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  //m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  //frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //setting up camera
  fbi = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
  fbi.SetVideoMode(cs::VideoMode::PixelFormat::kYUYV, 320, 240, 10);

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
  driveboi4.Follow(driveboi3, /*invert*/ false);
#ifdef Brit
  driveboi5.Follow(driveboi1, /*invert*/ false);
  driveboi6.Follow(driveboi3, /*invert*/ false);
#endif
}

void Robot::AutonomousPeriodic()
{

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
    if (batman.GetValue() > 375) //230 - 630 usable range
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
    if (batman.GetValue() > 250)
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
  frc::SmartDashboard::PutNumber("climber position", gwen.GetPosition());
  //read sensor
  double distance = batman.GetValue(); // * 0.393701; //multiplying by 0.393701 converts the sonar value to inches (hopefully)
  frc::SmartDashboard::PutNumber("Range Sensor 1", distance);

  // Code for deadzones on joystick
  notFarEnough = .05; /*todo: Adjust to driver's needs*/
  if (-lonelyStick->GetY() < notFarEnough || -lonelyStick->GetY() > -notFarEnough)
  {
#ifdef Brit
    lonelyY = lonelyStick->GetY();
#endif

#ifndef Brit
    lonelyY = -lonelyStick->GetY();
#endif
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

  //mike whipper/intake code
  if (neighborlyInputDevice->GetAButtonReleased())
  {
    toggle = -toggle;
    std::cout << "a button";
  }

  if (toggle == 1)
  {
    viagra.Set(false);
    simp.Set(0);
    whippedCheese.Set(ControlMode::PercentOutput, 0);
  }
  else if (toggle == -1)
  {
    viagra.Set(true);
    simp.Set(1);
    whippedCheese.Set(ControlMode::PercentOutput, .1);
  }

  //winch code
  if (neighborlyInputDevice->GetBButton())
  {
    whench.Set(.1);
  }

  //climber code
  if (neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand) > 0)
  {
    spoodermoon.Set(neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand) * .1);
  }
  else if (neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) > 0)
  {
    spoodermoon.Set(-neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) * .1);
  }
  else
  {
    spoodermoon.Set(0);
  }

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
#ifdef Brit
  spinReader5.SetPosition(0);
  spinReader6.SetPosition(0);
#endif
}

void Robot::Forwards()
{
  driveboi1.Set(-.1);
  driveboi3.Set(.1);
}
void Robot::Backwards()
{
  driveboi1.Set(.1);
  driveboi3.Set(-.1);
}
void Robot::Clock()
{
  driveboi1.Set(.1);
  driveboi3.Set(.1);
}
void Robot::CounterClock()
{
  driveboi1.Set(-.1);
  driveboi3.Set(-.1);
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif