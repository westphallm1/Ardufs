#include <Arduino.h>
#include "FileSystem.h"
#include <string.h>
FileSystem::FileSystem(){
  strcpy(_working_dir,"/");
}

FileSystem::~FileSystem(){

}

void FileSystem::ls(char * argv[]){
  Serial.println(".\n..");
  Serial.print("OK");
}

void FileSystem::cd(char * argv[]){
  _resolve_relative_path(argv[1]);
  if(_is_valid_path())
    strcpy(_working_dir,_staged_dir);
  Serial.print("OK");
}

void FileSystem::pwd(char * argv[]){
  Serial.println(_working_dir);
  Serial.print("OK");
}

int FileSystem::_is_valid_path(){
  return 1;
}

void FileSystem::_walk_back_path(int * end_idx){
  if(*end_idx < 3)
    return;
  *end_idx-=2;
  while(_staged_dir[*end_idx]!='/'){
    *end_idx -=1;
  };
  *end_idx+=1;
}

void FileSystem::_resolve_relative_path(char * path){
  if(path[0]=='/'){
    strcpy(_staged_dir,path);
    int len = strlen(path);
    if(path[len-1]!='/'){
      _staged_dir[len]='/';
      _staged_dir[len+1]='\0';
    }
  } else {
    //use a bunch of inefficient C string operations until we come up with
    //something better
    //start with our current dir
    strcpy(_staged_dir,_working_dir);
    //get the individuial directory names of _working_dir with strtok_r
    char *pathv[MAX_DIR_DEPTH];
    char * str = path;
    char * save = NULL;
    int i=0;
    while((pathv[i++] = strtok_r(str,"/",&save))!=NULL){
      str = NULL;
    };
    //append the paths one-by-one to the current path
    i = 0;
    int dir_len,base_len = strlen(_staged_dir);
    while(pathv[i]!=NULL){
      if(!strcmp(pathv[i],".")) {
          //change to current dir is a no-op
      } else if(!strcmp(pathv[i],"..")) {
        _walk_back_path(&base_len);
      }else {
        dir_len = strlen(pathv[i]);
        memcpy(_staged_dir+base_len,pathv[i], dir_len);
        base_len+=dir_len;
        _staged_dir[base_len]='/';
        base_len+=1;
      }
      i++;
    }
    _staged_dir[base_len]='\0';
  }
}
