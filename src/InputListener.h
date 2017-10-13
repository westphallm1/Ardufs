#ifndef InputListener_h
#define InputListener_h
#include<Arduino.h>
#define MAX_IN_BUFFER 128
#define MAX_ARGS 32
#define MAX_SEPS 10

class InputListener {
  public:
    InputListener(char * sep);
    ~InputListener();
    int listen();
    int hasNewCommand();
    void getNewCommand();
    int getCommandArgs(char * argv[]);
  private:
    char _sep[MAX_SEPS];
    char _in_buffr[MAX_IN_BUFFER];
    int _curr_char;
    int _has_new_line;
};

#endif
