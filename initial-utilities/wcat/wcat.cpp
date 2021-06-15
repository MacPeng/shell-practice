#include <iostream>
 
#include <fcntl.h>
#include <stdlib.h>
 
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
  int fd;
  if(argc < 1){
  exit(0);
}
  // see if the user passed in an argument
  if (argc == 1) {
    // it's already open
    fd = STDIN_FILENO;
  } else {
    for(int i = 1; i < argc; i++){
    fd = open(argv[i], O_RDONLY);
    if (fd < 0){
      cout << "wcat: cannot open file" << endl;
      exit(1);
   }else{
     char buffer[4098];
     int bytesRead = 0;
     int ret;

     while ((ret = read(fd, buffer, 4098)) > 0) {
     bytesRead += ret;
     write(STDOUT_FILENO, buffer, ret);
  }
  
 }
   if (argc != 1) {
     close(fd);
   } 
  }
 }

  return 0;
}
   
