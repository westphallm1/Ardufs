#include<Arduino.h>
#include"InputListener.h"
#include<string.h>


InputListener::InputListener(char * sep){
  strcpy(_sep, sep);
  _has_new_line = 0;
  _curr_char = 0;
}

InputListener::~InputListener(){

}

//must be called at every loop(). Reads a character from serial and checks
//for null terminator. Returns whether a character was read
int InputListener::listen(){
  //ignore characters recieved after the end of a line
  if(Serial.available() && !_has_new_line){
    _in_buffr[_curr_char]=Serial.read();
    //commands are null terminated
    if(_in_buffr[_curr_char]=='\0'){
      _has_new_line = 1;
    }
    _curr_char++;
    return 1;
  }
  return 0;
}

int InputListener::hasNewCommand(){
  return _has_new_line;
}

void InputListener::getNewCommand(){
  //clears out the command buffer and resets counter variables
  _has_new_line = 0;
  _curr_char = 0;
}

int InputListener::getCommandRaw(char ** text){
  if(!_has_new_line){
    //we didn't fill argv
    return 1;
  }
  *text = _in_buffr;
  _has_new_line=0;
  return 0;
};
int InputListener::getCommandArgs(char *argv[]){
  if(!_has_new_line){
    //we didn't fill argv
    return 1;
  }
  int i=0;
  //one liner to strtok_r the whole string
  char * save;
  while((argv[i++] = strtok_r((i==1)?_in_buffr:NULL," ",&save))!=NULL);

  _has_new_line=0;
  return 0;
}
