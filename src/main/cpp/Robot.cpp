/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "cscore.h"
#include "Robot.h"
#include <frc/Joystick.h>
#include <frc/drive/differentialDrive.h>
#include "rev/CANSparkMax.h"
#include <iostream>
#include <frc/SpeedControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <cameraserver/CameraServer.h>

//joystick creation
frc::Joystick *lonelyStick;

//tank drive creation
frc::DifferentialDrive *thomas; 

//motor creation
rev::CANSparkMax driveboi1 ( 2 , rev::CANSparkMax::MotorType::kBrushless );
rev::CANSparkMax driveboi2 ( 3 , rev::CANSparkMax::MotorType::kBrushless );
rev::CANSparkMax driveboi3 ( 4 , rev::CANSparkMax::MotorType::kBrushless );
rev::CANSparkMax driveboi4 ( 6 , rev::CANSparkMax::MotorType::kBrushless );

//motor groups
frc::SpeedControllerGroup speedyboiL ( driveboi1 , driveboi2 );
frc::SpeedControllerGroup speedyboiR ( driveboi3 , driveboi4 );

//camera creation
cs::UsbCamera fbi;

void Robot::RobotInit() 
{
  //m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  //m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  //frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //setting up camera
  fbi = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
    fbi.SetVideoMode ( cs::VideoMode::PixelFormat::kYUYV , 320 , 240 , 10 );

  //setting up joystick
  lonelyStick = new frc::Joystick(0);

  //setting up drivetrain
  thomas = new frc::DifferentialDrive( speedyboiL , speedyboiR );
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
double lonleyY = 0;
double lonleyTwist = 0;
double notFarEnough = .05;

if (-lonelyStick->GetY() < notFarEnough || -lonelyStick->GetY() > -notFarEnough)
{
  lonleyY = -lonelyStick->GetY();
}

if (lonelyStick->GetTwist() < notFarEnough || lonelyStick->GetTwist() > -notFarEnough)
{
  lonelyStick = lonelyStick->GetTwist();
}

thomas->ArcadeDrive(lonleyY , lonleyTwist);


}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
