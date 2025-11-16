#define MANUFACTURER_NAME "Dante Wackermann"
#define JOYSTICK_NAME "Opel GT Turn Signal Stalk"
#define SERIAL_NUMBER "LS-78342A"

// Custom VID/PID
#define USB_VID 0x2341
#define USB_PID 0x9A10

#define USB_DEVICE_DESCRIPTOR_OVERRIDE

#include "Joystick.h"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_GAMEPAD,
                   5, 0,                  // Button Count, Hat Switch Count
                   false, false, false,     // X and Y, but no Z Axis
                   false, false, false,   // No Rx, Ry, or Rz
                   false, false,          // No rudder or throttle
                   false, false, false);  // No accelerator, brake, or steering

void setup()
{
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP); // Blinker left
  pinMode(3, INPUT_PULLUP); // Blinker right
  pinMode(4, INPUT_PULLUP); // High beams
  pinMode(5, INPUT_PULLUP); // Side marker
  pinMode(6, INPUT_PULLUP); // Low beams

  Joystick.begin();

  Serial.println("Ready!");
}

int lastButtonState[5] = {0,0,0,0,0};

void loop()
{
  int aSize = sizeof(lastButtonState)/sizeof(int);

  for (int i=0; i<aSize;i++)
  {
    int state = !digitalRead(i+2);

    if(state != lastButtonState[i])
    {
      if(i==0 || i==1)
      {
        Joystick.setButton(i, 1);
        delay(100);
        Joystick.setButton(i, 0);
      }
      else
      {
        Joystick.setButton(i, state);
      }
      lastButtonState[i]=state;
    }
  }

  delay(10);
}