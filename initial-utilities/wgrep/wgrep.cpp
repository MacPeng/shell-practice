
#include <iostream>
#include <unistd.h>
#include <climits>
#include <cstring>
#include <string>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
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
         cout<<"wgrep: searchterm [file ...]"<<endl;
        exit(1);
    } else {
        int k = argc;
        if(argc == 2){
            k = 3;
        }
        for(int i = 2; i < k; i++){
            //i starts from 2 bcoz 1 is the target word; i=2 use std input
            if(argc == 2){
                fd = STDIN_FILENO;
            }else{
                fd = open(argv[i], O_RDONLY);
            }

            if (fd < 0){
                cout << "wgrep: cannot open file" << endl;
                exit(1);
            }else{
                char buffer[4098];

                char *str = (char*)malloc(sizeof(char)*INT_MAX); //dynamically distribute memory space
                char *target = argv[1];
                int bytesRead = 0;
                int ret;
                int j = 0;
                while ((ret = read(fd, buffer, 1)) > 0) {

                    if(buffer[0] == '\n'){
                      if(strstr(str, target)){

                           str[j] = buffer[0];  //find \n
                        write(STDOUT_FILENO, str, (int)strlen(str));
                      }
                        free(str);
                        str = (char*)calloc(sizeof(char), INT_MAX);// set all memory to zero
                     j = 0;
                     bytesRead ++;
                        continue;// jump the nexzt line
                    }
                 str[j] = buffer[0];
                 j++;
                 bytesRead ++;
                }
               free(str);
            }
           // if (argc != 1) {
                close(fd);
        //}


        }
    }

    return 0;
}


