#include "Editor.h"
#include <string.h>

//TODO override existing files
Editor::Editor(char * fname){
  _file = SD.open(fname,'w');
}

Editor::~Editor(){
  close();
}

void Editor::close(){
  _file.close();
}
int Editor::writeLine(char *line){
  _file.write(line,strlen(line));
  _file.write('\n');
  return 1;
}
