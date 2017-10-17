#ifndef FileNavigator_h
#define FileNavigator_h
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#define MAX_BUFFER 64
#define MAX_DIR_DEPTH 16
#define CHIP_SELECT 4
#define PRINT_BAD_PATH_MSG(path)Serial.print(path);\
                          Serial.println(": No such directory.");

//ls only works once so we need to store the results ourselves (put in file?)
class FileNavigator {
  public:
    FileNavigator();
    FileNavigator(struct file_navigator_cache * cache);
    ~FileNavigator();
    void ls(char *argv[]);
    void cd(char * argv[]);
    void pwd(char * argv[]);
    void mkdir(char * argv[]);
    void rmdir(char * argv[]);
    void cat(char * argv[]);
    void rm(char * argv[]);
    void cache(file_navigator_cache * cache);
    char * workingDir();
    static void resolveRelativePath(char * current, char * change,
      char *dest,int isDir);
  private:
    static void _walk_back_path(int * end_idx, char * path);
    char _working_dir[MAX_BUFFER];
    char _staged_dir[MAX_BUFFER];
    void _print_files_in(File * dir_f);
    int _is_valid_path(char * dir);
    void _resolve_relative_path(char * path, int isDirectory);
    void _cat_from_file(char * fname);
};


#endif
