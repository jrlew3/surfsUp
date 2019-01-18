#include <SerialCommand.h>
#include <AccelStepper.h>
#include <SoftwareSerial.h>

SerialCommand cmd; 
AccelStepper stepper(AccelStepper::FULL2WIRE, 2, 3); 

const int defaultLength = 5000;
 
void setup() {
  Serial.begin(9600);
  while(!Serial); 
  stepper.setMaxSpeed(1000);
    
  cmd.addCommand("MOVE", moveHandler); 
}

void moveRight(int velocity) { 
  stepper.moveTo(defaultLength);
  stepper.setSpeed(velocity);     
}

void moveLeft(int velocity) { 
  stepper.moveTo(0); 
  stepper.setSpeed(velocity); 
}


void loop() {
  
  if(Serial.available() > 0) {
    cmd.readSerial(); 
  }
  stepper.runSpeed();
}

void moveHandler() { 
  String arg = (String) cmd.next(); 
  if(arg == NULL) return; 
  
  int velocity = arg.toInt(); 
  if(velocity > 0) moveRight(velocity); 
  else moveLeft(velocity); 
  
}
