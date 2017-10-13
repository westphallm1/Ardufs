#ifndef CommandRouter_h
#define CommandRouter_h
#include<Arduino.h>
#include "FileSystem.h"
class CommandRouter {
  public:
    CommandRouter(FileSystem * fs);
    void route(char *args[]);
  private:
    FileSystem * _fs;

};


#endif
