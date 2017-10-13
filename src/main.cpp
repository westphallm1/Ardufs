#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "InputListener.h"
#include "FileSystem.h"
#include "CommandRouter.h"
#include <string.h>

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
char * args[10];

// the setup routine runs once when you press reset:
InputListener * parser = new InputListener((char *)(" ,"));
FileSystem * fs = new FileSystem();

CommandRouter * router = new CommandRouter(fs);
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  parser->listen();
  if(parser->hasNewCommand()){
    //fill in the argument vector
    parser->getCommandArgs(args);
    //run the appropriate command
    router->route(args);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    //clear the command buffer
    parser->getNewCommand();
  }
}
