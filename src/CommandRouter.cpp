#include "CommandRouter.h"
CommandRouter::CommandRouter(FileSystem * fs){
  _fs = fs;
}

//TODO more efficient way of command lookup
void CommandRouter::route(char **args){
  if(!strcmp(args[0],"ls"))
    _fs->ls(args);
  else if(!strcmp(args[0],"cd"))
    _fs->cd(args);
  else if(!strcmp(args[0],"pwd"))
    _fs->pwd(args);
}
