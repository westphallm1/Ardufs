#ifndef Editor_h
#define Editor_h
#include<Arduino.h>
#include <SPI.h>
#include <SD.h>
class Editor {
  public:
    Editor(char * fname);
    ~Editor();
    int writeLine(char * line);
    void close();
  private:
    File _file;
    int _curr_char;
    int _has_new_line;
};

#endif
