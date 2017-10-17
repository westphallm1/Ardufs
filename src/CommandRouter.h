#ifndef CommandRouter_h
#define CommandRouter_h
#include<Arduino.h>
#include "FileNavigator.h"
#include "InputListener.h"
#include "Editor.h"

enum console_mode {SHELL,EDITOR};
class CommandRouter {
  public:
    CommandRouter();
    void route(InputListener * listner);
  private:
    FileNavigator * _fn;
    Editor * _ed;
    enum console_mode mode;
    void _setupFileNavigator();
    void _unsetFileNavigator();
};


#endif
