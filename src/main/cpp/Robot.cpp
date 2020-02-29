#include "Robot.h"
#include <C:\Users\robok\Documents\2020BasicDriveCode\src\main\cpp\Variables\Variables.h>

void Robot::RobotInit()
{
  //setting up cameras
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

  //brit motors
  driveboi1 = new rev::CANSparkMax(7, rev::CANSparkMax::MotorType::kBrushless);
  driveboi2 = new rev::CANSparkMax(10, rev::CANSparkMax::MotorType::kBrushless);
  driveboi3 = new rev::CANSparkMax(13, rev::CANSparkMax::MotorType::kBrushless);
  driveboi4 = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless);
  driveboi5 = new rev::CANSparkMax(8, rev::CANSparkMax::MotorType::kBrushless);
  driveboi6 = new rev::CANSparkMax(9, rev::CANSparkMax::MotorType::kBrushless);

  //brit motor groups
  speedyboiL = new frc::SpeedControllerGroup(*driveboi1, *driveboi2, *driveboi3);
  speedyboiR = new frc::SpeedControllerGroup(*driveboi4, *driveboi5, *driveboi6);

  //Encoder creation
  spinReader1 = driveboi1->GetEncoder();
  spinReader2 = driveboi2->GetEncoder();
  spinReader3 = driveboi3->GetEncoder();
  spinReader4 = driveboi4->GetEncoder();
  spinReader5 = driveboi5->GetEncoder();
  spinReader6 = driveboi6->GetEncoder();

  //winch encoder creation
  pimp = whench->GetEncoder();
  //climber encoder creation
  gwen = spoodermoon->GetEncoder();

  //winch motor creation
  whench = new rev::CANSparkMax(12, rev::CANSparkMax::MotorType::kBrushless);
  //climber motor creation
  spoodermoon = new rev::CANSparkMax(11, rev::CANSparkMax::MotorType::kBrushless);
  //mike whipper motor creation
  whippedCheese = new ctre::phoenix::motorcontrol::can::VictorSPX(25);
  //mike whipper up/down solenoid
  viagra = new frc::Solenoid(3);
  //intake motor creation
  simp = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless);
  egirl = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);

  //setting up drivetrain
  brit = new frc::DifferentialDrive(*speedyboiL, *speedyboiR);

  //sonlenoid
  peerPressure1 = new frc::Solenoid(0);
  peerPressure2 = new frc::Solenoid(1);
  roboMyRio = new frc::Solenoid(2);

  //compressor
  bonusPressure = new frc::Compressor(0);

  //limit switch
  stopIt = new frc::DigitalInput(9);

  //setting up us sensor
  batman = new frc::AnalogInput(0);

  //mike whipper and intake variable
  toggle = 1;
}

void Robot::RobotPeriodic()
{
}

void Robot::AutonomousInit()
{
  Robot::AutownInit();
}

void Robot::AutonomousPeriodic()
{
  Robot::AutownPeriodic();
}

void Robot::TeleopInit()
{
}

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
  double distance = batman->GetValue() * 0.393701; //multiplying by 0.393701 converts the sonar value to inches (hopefully)
  frc::SmartDashboard::PutNumber("Range Sensor 1", distance);

  // Code for deadzones on joystick
  notFarEnough = .05;
  if (-lonelyStick->GetY() < notFarEnough || -lonelyStick->GetY() > -notFarEnough)
  {
    lonelyY = lonelyStick->GetY();
  }
  if (lonelyStick->GetTwist() < notFarEnough || lonelyStick->GetTwist() > -notFarEnough)
  {
    lonelyTwist = -lonelyStick->GetTwist();
  }

  //making the compressor compress
  bonusPressure->SetClosedLoopControl(true);

  //gearbox shifting code
  peerPressure2->Set(lessSpeed->Get());
  peerPressure1->Set(moreSpeed->Get());

  //pneumatic actuator
  if (putItIn->Get())
  {
    roboMyRio->Set(true);
    Robot::Wait(.5);
    roboMyRio->Set(false);
  }

  //mike whipper and intake code
  if (neighborlyInputDevice->GetAButtonReleased())
  {
    toggle = -toggle;
  }

  if (toggle == 1)
  {
    viagra->Set(false);
    simp->Set(0);
    egirl->Set(0);
    whippedCheese->Set(ControlMode::PercentOutput, 0);
  }
  else if (toggle == -1)
  {
    viagra->Set(true);
    simp->Set(.5);
    egirl->Set(-.5);
    whippedCheese->Set(ControlMode::PercentOutput, 0.8);
  }

  //winch code
  if (neighborlyInputDevice->GetBButton())
  {
    whench->Set(1);
  }
  else
  {
    whench->Set(0);
  }

  //climber code
  if (neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand) > 0)
  {
    spoodermoon->Set(-neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand) * .2);
  }
  else if (neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) > 0)
  {
    spoodermoon->Set(neighborlyInputDevice->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) * .2);
  }
  else
  {
    spoodermoon->Set(0);
  }

  //Bumber to preset climbing positions (63 in and all the way down)
  if (neighborlyInputDevice->GetBumper(frc::GenericHID::JoystickHand::kRightHand) && -gwen.GetPosition() < 82)
  {
    spoodermoon->Set(-.2);
  }
  else if (neighborlyInputDevice->GetBumper(frc::GenericHID::JoystickHand::kLeftHand) && -gwen.GetPosition() > 0)
  {
    spoodermoon->Set(.2);
  }

  //90 Degree turn code (Not Tested)
  /*if ()
  {
  }
  else if ()
  {
    Robot::Clock();
  }
  else
  {
    ZeroMotors();
  }*/

  speed = .8;

  brit->ArcadeDrive(lonelyY * speed, lonelyTwist * speed);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif