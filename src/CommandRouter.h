#ifndef CommandRouter_h
#define CommandRouter_h
#include<Arduino.h>
#include "FileNavigator.h"
class CommandRouter {
  public:
    CommandRouter(FileNavigator * fn);
    void route(char *args[]);
  private:
    FileNavigator * _fn;

};


#endif
