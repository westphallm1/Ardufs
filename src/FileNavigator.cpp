#include <Arduino.h>
#include "FileNavigator.h"
#include <string.h>

/*
 * Public Functions
 */

FileNavigator::FileNavigator(){
  strcpy(_working_dir,"/");
}

FileNavigator::~FileNavigator(){

}

/*
 * List the files in the specified directories
 */
void FileNavigator::ls(char * argv[]){
  if(argv[1]==NULL){
    File root = SD.open(_working_dir);
    _print_files_in(&root);
    root.close();
  }else{
    int i=1;
    while(argv[i++]!=NULL){
      _resolve_relative_path(argv[i],1);
      File curr = SD.open(_staged_dir);
      _print_files_in(&curr);
      curr.close();
    }
  }

}

/*
 * Change the working directory
 */
void FileNavigator::cd(char * argv[]){
  if(argv[1]==NULL){
    strcpy(_working_dir,"/");
  }else{
    _resolve_relative_path(argv[1],1);
    if(_is_valid_path(_staged_dir))
      strcpy(_working_dir,_staged_dir);
    else {
      PRINT_BAD_PATH_MSG(argv[1]);
    }
  }
}

/*
 * Print the working directory
 */
void FileNavigator::pwd(char * argv[]){
  Serial.println(_working_dir);
}

/*
 * Add a directory to the filesystem
 */
void FileNavigator::mkdir(char * argv[]){
  if(argv[1]!=NULL){
    _resolve_relative_path(argv[1],1);
    if(!SD.mkdir(_staged_dir)){
      Serial.print("Failed to make directory ");
      Serial.print(argv[1]);
    };
  }
}

/*
 * Remove a directory from the filesystem
 */
void FileNavigator::rmdir(char * argv[]){
  if(argv[1]!=NULL){
    _resolve_relative_path(argv[1],1);
    SD.rmdir(_staged_dir);
  }
}

/*
 * Print the contents of a file ($ cat fname),
 * or write to a file ($ cat > fname)
 */
void FileNavigator::cat(char * argv[]){
  if(!strcmp(argv[1],">")){
    _cat_to_file(argv[2]);
  } else {
    _cat_from_file(argv[1]);
  }
}
/*
 * Private Functions
 */

 /*
  * Check whether a file/directory exists on the SD card
  */
int FileNavigator::_is_valid_path(char * dir){
  if(!strcmp(dir,"/"))
    return 1;
  //exists seems to mess with the name that's passed to it
  char dir_copy[16];
  strcpy(dir_copy,dir);
  int exists = SD.exists(dir_copy);
  return exists;
}

/*
 * Utility to help parse paths with upward directory changes
 */
void FileNavigator::_walk_back_path(int * end_idx){
  if(*end_idx < 3)
    return;
  *end_idx-=2;
  while(_staged_dir[*end_idx]!='/'){
    *end_idx -=1;
  };
  *end_idx+=1;
}

/*
 * Figure out the absolute path given a relative path and the current directory
 */
void FileNavigator::_resolve_relative_path(char * path,int isDirectory){
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
    if(isDirectory)
      _staged_dir[base_len]='\0';
    else
      _staged_dir[base_len-1]='\0';
  }
}

/*
 * Helper function for ls, print current files in a directory
 */
void FileNavigator::_print_files_in(File * dir_f){
  dir_f ->rewindDirectory();
  File entry;
  while((entry=dir_f->openNextFile())){
    Serial.print(entry.name());
    int isDirectory = entry.isDirectory();
    Serial.println((isDirectory)?"/":"");
    entry.rewindDirectory();
    /*if(isDirectory)
      _print_files_in(&entry);*/
    entry.close();
  };
  dir_f->rewindDirectory();
  dir_f->close();
}

/*
 * Print the current contents of a file to serial
 */
void FileNavigator::_cat_from_file(char * fname){
  _resolve_relative_path(fname,0);
  File toCat = SD.open(_staged_dir);
  if(toCat){
    while(toCat.available()){
      Serial.write(toCat.read());
    }
  }else{
    Serial.print("Couldn't open file ");
    Serial.println(fname);
  }
  toCat.close();
}

/*
* Print from serial to a file
*/
void FileNavigator::_cat_to_file(char * fname){

}
