#pragma once
#include <Robot.h>

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
