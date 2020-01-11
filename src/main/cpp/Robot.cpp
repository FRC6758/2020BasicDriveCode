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

//joystick creation
frc::Joystick *lonelyStick;
frc::JoystickButton *nuke;

//controller creation
frc::XboxController *neighborlyInputDevice;

//tank drive creation
frc::DifferentialDrive *thomas; 

//motor creation
rev::CANSparkMax driveboi1 (  1 /*2*/ , rev::CANSparkMax::MotorType::kBrushless );
rev::CANSparkMax driveboi2 (  10 /*3*/ , rev::CANSparkMax::MotorType::kBrushless );
// rev::CANSparkMax driveboi3 ( 4 , rev::CANSparkMax::MotorType::kBrushless );
// rev::CANSparkMax driveboi4 ( 6 , rev::CANSparkMax::MotorType::kBrushless );

//motor groups
// frc::SpeedControllerGroup speedyboiL ( driveboi1 , driveboi2 );
// frc::SpeedControllerGroup speedyboiR ( driveboi3 , driveboi4 );


//camera creation
cs::UsbCamera fbi;
frc::Solenoid peerPressure (0);
frc::DigitalInput limitSwitch (4);


void Robot::RobotInit() 
{
  //m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  //m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  //frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //setting up camera
  fbi = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
    fbi.SetVideoMode ( cs::VideoMode::PixelFormat::kYUYV , 320 , 240 , 10 );

  //setting up joystick
  lonelyStick = new frc::Joystick ( 1 );

  //setting up controller
  neighborlyInputDevice = new frc::XboxController ( 0 );

  lonelyStick = new frc::Joystick(0);
  nuke = new frc::JoystickButton( lonelyStick, 3);
  //setting up drivetrain

  thomas = new frc::DifferentialDrive( driveboi1/*speedyboiL*/ , driveboi2/*speedyboiR*/ );
 
 
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

  if (m_autoSelected == kAutoNameCustom) 
  {
    // Custom Auto goes here
  } 
  else 
  {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() 
{
  if (m_autoSelected == kAutoNameCustom) 
  {
    // Custom Auto goes here
  } 
  else 
  {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() 
{


// Code for deadzones on joystick
double lonelyY = 0;
double lonelyTwist = 0;
double notFarEnough = .05 /*todo: Adjust to driver's needs*/;

if (-lonelyStick->GetY() < notFarEnough || -lonelyStick->GetY() > -notFarEnough)
{
  lonelyY = -lonelyStick->GetY();
}

if (lonelyStick->GetTwist() < notFarEnough || lonelyStick->GetTwist() > -notFarEnough)
{
  lonelyTwist = lonelyStick->GetTwist();
}

thomas->ArcadeDrive(lonelyY , lonelyTwist);

/*//joystick values to movement in drivetrain
thomas->ArcadeDrive ( -lonelyStick->GetY () , lonelyStick->GetTwist () );*/

//controller values to movement in drivetrain
//thomas->ArcadeDrive ( neighborlyInputDevice->GetY ( frc::GenericHID::JoystickHand::kLeftHand ) , neighborlyInputDevice->GetX ( frc::GenericHID::JoystickHand::kLeftHand ) );

//testing to use controller
/*double testingboi = neighborlyInputDevice->GetX(frc::GenericHID::JoystickHand::kLeftHand);
if ( testingboi > 0 ) {
  std::cout << "x axis is goin \n";
}*/

peerPressure.Set(nuke->Get() || limitSwitch.Get());



}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
