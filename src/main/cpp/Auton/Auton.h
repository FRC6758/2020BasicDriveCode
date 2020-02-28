#pragma once
#include <Robot.h>
#include <C:\Users\xv63yk\Documents\GitHub\2020BasicDriveCode\src\main\Variables\Variables.h>

void Robot::AutonomousInit2()
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
  driveboi5.Follow(driveboi1, /*invert*/ false);
  driveboi6.Follow(driveboi3, /*invert*/ false);
}

void Robot::AutonomousPeriodic2()
{

  double forwardBackward = spinReader1.GetPosition() - spinReader3.GetPosition();
  double turn = spinReader1.GetPosition() + spinReader3.GetPosition();
  /*if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } 
  else {
    // Default Auto goes here
  }*/

  // Ultra Sonic Straight Shot (Best Option) (Not Tested)
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

  //UltraSonic Side Shot (2nd Best Option) (Not Tested)
  /*
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
*/
}