/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "cscore.h"
#include <string>
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
#include <time.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutownInit();
  void AutonomousPeriodic() override;
  void AutownPeriodic();
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void ZeroMotors();
  void Forwards();
  void Backwards();
  void Clock();
  void CounterClock();
  void Wait(double);

private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

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
  rev::CANSparkMax *driveboi1;
  rev::CANSparkMax *driveboi2;
  rev::CANSparkMax *driveboi3;
  rev::CANSparkMax *driveboi4;
  rev::CANSparkMax *driveboi5;
  rev::CANSparkMax *driveboi6;

  //brit motor groups
  frc::SpeedControllerGroup *speedyboiL;
  frc::SpeedControllerGroup *speedyboiR;

  //Encoder creation
  rev::CANEncoder spinReader1;
  rev::CANEncoder spinReader2;
  rev::CANEncoder spinReader3;
  rev::CANEncoder spinReader4;
  rev::CANEncoder spinReader5;
  rev::CANEncoder spinReader6;

  //winch encoder creation
  rev::CANEncoder pimp;
  //climber encoder creation
  rev::CANEncoder gwen;

  //winch motor creation
  rev::CANSparkMax *whench;
  //climber motor creation
  rev::CANSparkMax *spoodermoon;
  //mike whipper motor creation
  ctre::phoenix::motorcontrol::can::VictorSPX *whippedCheese;
  //mike whipper up/down solenoid
  frc::Solenoid *viagra;
  //intake motor creation
  rev::CANSparkMax *simp;
  rev::CANSparkMax *egirl;

  //camera creation
  cs::UsbCamera fbi;
  cs::UsbCamera cia;

  //ultrasonic range sensor creation
  frc::AnalogInput *batman; // 230 - 630 is usable range
  //ultrsonic variable
  double distance;

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
  frc::Solenoid *peerPressure1;
  frc::Solenoid *peerPressure2;
  frc::Solenoid *roboMyRio;

  //compressor creation
  frc::Compressor *bonusPressure;

  //limit switch creation
  frc::DigitalInput *stopIt;

  //revolution var
  int forwardBackwardDistance;
  int turnDistance;

  //toggle variable for intake things
  int toggle;

  //speed var
  double speed;

  //Dead Zone Variables
  double lonelyY;
  double lonelyTwist;
  double notFarEnough;
};
