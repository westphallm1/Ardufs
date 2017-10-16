#ifndef FileNavigator_h
#define FileNavigator_h
#include<Arduino.h>
#include <SPI.h>
#include <SD.h>
#define MAX_BUFFER 64
#define MAX_DIR_DEPTH 16
#define CHIP_SELECT 4
#define PRINT_BAD_PATH_MSG(path)Serial.print(path);\
                          Serial.println(": No such directory.");

//ls only works once so we need to store the results ourselves (put in file?)
struct dir_node{
  struct dir_node * child_files;
  struct dir_node * child_dirs;
  char name[16];
};

class FileNavigator {
  public:
    FileNavigator();
    ~FileNavigator();
    void ls(char *argv[]);
    void cd(char * argv[]);
    void pwd(char * argv[]);
    void mkdir(char * argv[]);
    void rmdir(char * argv[]);
  private:
    int _has_cached_dirs;
    char _working_dir[MAX_BUFFER];
    char _staged_dir[MAX_BUFFER];
    void _print_files_in(File * dir_f);
    void _walk_back_path(int * end_idx);
    int _is_valid_path(char * dir);
    void _resolve_relative_path(char * path);
};


#endif
