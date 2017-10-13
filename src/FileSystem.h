#ifndef FileSystem_h
#define FileSystem_h
#include<Arduino.h>
#define MAX_BUFFER 256
#define MAX_DIR_DEPTH 32
class FileSystem {
  public:
    FileSystem();
    ~FileSystem();
    void ls(char *argv[]);
    void cd(char * argv[]);
    void pwd(char * argv[]);
  private:
    char _working_dir[MAX_BUFFER];
    char _staged_dir[MAX_BUFFER];
    void _walk_back_path(int * end_idx);
    int _is_valid_path();
    void _resolve_relative_path(char * path);
};


#endif
