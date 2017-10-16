#include "CommandRouter.h"
CommandRouter::CommandRouter(FileNavigator * fn){
  _fn = fn;
}

//TODO more efficient way of command lookup
void CommandRouter::route(char **args){
  if(!strcmp(args[0],"login"))
    Serial.println("ArduFS Shell v0.1");
  else if(!strcmp(args[0],"ls"))
    _fn->ls(args);
  else if(!strcmp(args[0],"cd"))
    _fn->cd(args);
  else if(!strcmp(args[0],"pwd"))
    _fn->pwd(args);
  else if(!strcmp(args[0],"mkdir"))
    _fn->mkdir(args);
  else if(!strcmp(args[0],"rmdir"))
    _fn->rmdir(args);
  else if(!strcmp(args[0],"cat"))
    _fn->cat(args);
  else{
    Serial.print("Command \"");
    Serial.print(args[0]);
    Serial.println("\" not recognized.");
  }
  Serial.print("$ ");
  Serial.print("OK");
}
