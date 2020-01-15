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
frc::JoystickButton *nuke; //button 3
frc::JoystickButton *oneSpin; //button 4
//controller creation
frc::XboxController *neighborlyInputDevice;

//tank drive creation
frc::DifferentialDrive *thomas; 

//motor creation
rev::CANSparkMax driveboi1 ( 2 , rev::CANSparkMax::MotorType::kBrushless );
rev::CANSparkMax driveboi2 ( 3 , rev::CANSparkMax::MotorType::kBrushless );
rev::CANSparkMax driveboi3 ( 4 , rev::CANSparkMax::MotorType::kBrushless );
rev::CANSparkMax driveboi4 ( 6 , rev::CANSparkMax::MotorType::kBrushless );
//rev::CANSparkMax driveboi5 ( 7 , rev::CANSparkMax::MotorType::kBrushless );
//rev::CANSparkMax driveboi6 ( 8 , rev::CANSparkMax::MotorType::kBrushless );

//motor groups
frc::SpeedControllerGroup speedyboiL ( driveboi1 , driveboi2 /*, driveboi5*/ );
frc::SpeedControllerGroup speedyboiR ( driveboi3 , driveboi4 /*, driveboi6*/ );


//camera creation
cs::UsbCamera fbi;

//sonlenoid creation
frc::Solenoid peerPressure (0);

//limit switch creation
frc::DigitalInput limitSwitch (4);

//Encoder creation 
rev::CANEncoder spinReader1 = driveboi1.GetEncoder();
rev::CANEncoder spinReader2 = driveboi2.GetEncoder();
rev::CANEncoder spinReader3 = driveboi3.GetEncoder();
rev::CANEncoder spinReader4 = driveboi4.GetEncoder();
//rev::CANEncoder spinReader5 = driveboi5.GetEncoder();
//rev::CANEncoder spinReader6 = driveboi6.GetEncoder();

//Dead Zone Variables
double lonelyY = 0;
double lonelyTwist = 0;
double notFarEnough = .05 /*todo: Adjust to driver's needs*/;



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
  oneSpin = new frc::JoystickButton( lonelyStick, 4);
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
  //driveboi2.Follow (driveboi1, /*invert*/ false);
  //driveboi4.Follow (driveboi3, /*invert*/ false);

  /*if (m_autoSelected == kAutoNameCustom) 
  {
    // Custom Auto goes here

  } 
  else 
  {
    // Default Auto goes here
  }*/
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() 
{


//42 counts per rev. on neo
if(spinReader1.GetVelocity() == 0) spinReader1.SetPosition(0);
if(spinReader2.GetVelocity() == 0) spinReader2.SetPosition(0);
if(spinReader3.GetVelocity() == 0) spinReader3.SetPosition(0);
if(spinReader4.GetVelocity() == 0) spinReader4.SetPosition(0);
//if(spinReader5.GetVelocity() == 0) spinReader5.SetPosition(0);
//if(spinReader6.GetVelocity() == 0) spinReader6.SetPosition(0);

//Read Encoder
frc::SmartDashboard::PutNumber("Encoder1 Position", spinReader1.GetPosition());
frc::SmartDashboard::PutNumber("Encoder2 Position", spinReader2.GetPosition());
frc::SmartDashboard::PutNumber("Encoder3 Position", spinReader3.GetPosition());
frc::SmartDashboard::PutNumber("Encoder4 Position", spinReader4.GetPosition());
//frc::SmartDashboard::PutNumber("Encoder5 Position", spinReader5.GetPosition());
//frc::SmartDashboard::PutNumber("Encoder6 Position", spinReader6.GetPosition());

// Code for deadzones on joystick
if (-lonelyStick->GetY() < notFarEnough || -lonelyStick->GetY() > -notFarEnough)
{
  lonelyY = -lonelyStick->GetY();
}
if (lonelyStick->GetTwist() < notFarEnough || lonelyStick->GetTwist() > -notFarEnough)
{
  lonelyTwist = lonelyStick->GetTwist();
}
thomas->ArcadeDrive(lonelyY *.2 , lonelyTwist * .2);

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

void Robot::TestPeriodic() {
//back motors following front motors
driveboi2.Follow (driveboi1, /*invert*/ false);
driveboi4.Follow (driveboi3, /*invert*/ false);
//driveboi5.Follow (driveboi1, /*invert*/ false);
//driveboi6.Follow (driveboi3, /*invert*/ false);

//Motor spins once with Joystick button
if (spinReader1.GetPosition() < 10) driveboi1.Set(.25);
//if (spinReader1.GetPosition() < 10) driveboi1.Set(.99^spinReader1.GetPosition());
else driveboi1.Set(0);

if (spinReader3.GetPosition() > -10) driveboi3.Set(-.25);
//if (spinReader3.GetPosition() > -10) driveboi3.Set(-.99^spinReader3.GetPosition());
else driveboi3.Set(0);

if (oneSpin->Get()) {
  spinReader1.SetPosition(0);
  spinReader3.SetPosition(0);
}

/*motor group = .99^encoder value
motor group = -.99^encoder value
make sure the opposite encoder stuff is the opposite otherwise as it counts up it will keep getting faster/ need two different equations
driveboi1.Set(.99^spinReader1.GetPosition()) for the positive side
*/
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
