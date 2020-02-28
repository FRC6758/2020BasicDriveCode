#include "Robot.h"
#include <C:\Users\xv63yk\Documents\GitHub\2020BasicDriveCode\src\main\Auton\Auton.h>
#include <C:\Users\xv63yk\Documents\GitHub\2020BasicDriveCode\src\main\Variables\Variables.h>

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
  Robot::AutonomousInit2();
}

void Robot::AutonomousPeriodic()
{
  Robot::AutonomousPeriodic2();
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
  if (putItIn->Get())
  {
    roboMyRio.Set(true);
    Robot::Wait(.5);
    roboMyRio.Set(false);
  }

  //mike
  //intake code
  if (neighborlyInputDevice->GetAButtonReleased())
  {
    toggle = -toggle;
  }

  if (toggle == 1)
  {
    viagra.Set(false);
    simp.Set(0);
    whippedCheese.Set(ControlMode::PercentOutput, 0); //should be 0 just testing
  }
  else if (toggle == -1)
  {
    viagra.Set(true);
    simp.Set(.5);
    whippedCheese.Set(ControlMode::PercentOutput, .8); //should be .1 just testing
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
  if (neighborlyInputDevice->GetBumper(frc::GenericHID::JoystickHand::kRightHand) && -gwen.GetPosition() < 82)
  {
    spoodermoon.Set(-.2);
  }
  else if (neighborlyInputDevice->GetBumper(frc::GenericHID::JoystickHand::kLeftHand) && -gwen.GetPosition() > 0)
  {
    spoodermoon.Set(.2);
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
  driveboi1.Set(-.5);
  driveboi3.Set(.5);
}
void Robot::Backwards()
{
  driveboi1.Set(.5);
  driveboi3.Set(-.5);
}
void Robot::Clock()
{
  driveboi1.Set(.5);
  driveboi3.Set(.5);
}
void Robot::CounterClock()
{
  driveboi1.Set(-.5);
  driveboi3.Set(-.5);
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