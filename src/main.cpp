#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "InputListener.h"
#include "FileNavigator.h"
#include "CommandRouter.h"
#include <string.h>

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#define led 13
// the setup routine runs once when you press reset:
InputListener * parser = new InputListener((char *)(" ,"));
CommandRouter * router = new CommandRouter();
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  if(!SD.begin(CHIP_SELECT)) {
    Serial.println("Error: Failed to Open SD Card.");
    Serial.print("NOK");
  }
}

// the loop routine runs over and over again forever:
void loop() {
  parser->listen();
  if(parser->hasNewCommand()){
    //fill in the argument vector
    //run the appropriate command
    router->route(parser);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    //clear the command buffer
    parser->getNewCommand();
  }
}
