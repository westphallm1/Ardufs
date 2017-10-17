#include "CommandRouter.h"

CommandRouter::CommandRouter(){
  _fn = new FileNavigator();
  mode = SHELL;
}
//move the various command handlers into and out of memory
//TODO more efficient way of command lookup
void CommandRouter::route(InputListener * listener){
  char * args[10];
  char * text;
  if(mode==SHELL){
    listener->getCommandArgs(args);
    //ignore empty input
    if(args[0][0]=='\0'){
      return;
    }
    if(!strcmp(args[0],"login")){
      Serial.println("ArduFS Shell v0.1");
    }else if(!strcmp(args[0],"ls")){
      _fn->ls(args);
    }else if(!strcmp(args[0],"cd")){
      _fn->cd(args);
    }else if(!strcmp(args[0],"pwd")){
      _fn->pwd(args);
    }else if(!strcmp(args[0],"mkdir")){
      _fn->mkdir(args);
    }else if(!strcmp(args[0],"rmdir")){
      _fn->rmdir(args);
    }else if(!strcmp(args[0],"rm")){
      _fn->rm(args);
    }else if(!strcmp(args[0],"cat")){
      if(!strcmp(args[1],">")){
        //this is a bit ugly
        char new_path[64];
        FileNavigator::resolveRelativePath(_fn->workingDir(),args[2],new_path,0);
        _ed = new Editor(new_path);
        mode=EDITOR;
      }else{
        _fn->cat(args);
      }
    }else{
      Serial.print("Command \"");
      Serial.print(args[0]);
      Serial.println("\" not recognized.");
    }
  }else if(mode==EDITOR){
    listener->getCommandRaw(&text);
    if(!strcmp(text,"EOF")){
      delete _ed;
      mode=SHELL;
    }else{
      _ed->writeLine(text);
    }

  }
  if(mode==SHELL)
    Serial.print("$ ");
  Serial.print("OK");
}
