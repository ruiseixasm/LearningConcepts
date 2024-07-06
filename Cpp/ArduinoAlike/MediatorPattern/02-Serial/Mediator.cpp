#include "Mediator.h"


// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

void mediatorSetup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
}

void mediatorLoop()
{
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  //Serial.println(buttonState);  // DOESN'T COMPILE!
  delay(1);        // delay in between reads for stability
}