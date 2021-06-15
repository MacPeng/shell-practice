
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
    int j = 1; // if teseted 0 so starts from 1
    int k=1; // if teseted 0 so starts from 1
    int counter = 0;
    char end;
    // see if the user passed in an argument
    if (argc < 2) {
        // it's already open
        cout<<"wzip: file1 [file2 ...]"<<endl;
        exit(1);
    } else {
        int fd;
        int* int1 = (int*)malloc(sizeof(int) * INT_MAX); //make an int array to put the # of chars
        //int32_t int1 = 1; //int32 bcoz int has 4 bytes=32 bits
        char* ch = (char*)malloc(sizeof(char) * INT_MAX); // put diff chars in
        //string ch;
        int ret;
        for(int i = 1; i < argc; i++){
          fd = open(argv[i], O_RDONLY);
            if(fd < 0){
                cout<<"wzip: cannot open file"<<endl;
                exit(1);
            }
            else{
                char* buffer = (char*)malloc(sizeof(char) * INT_MAX);
                
                //char buffer[4098];
                while ((ret = read(fd, buffer, 1)) > 0) {
                    //cout<<"ahsh"<<endl;
                
                    if(counter == 0){
                        ch[0] = buffer[0];
                        int1[0] = 1;
                        counter = 1;
                        //continue;
                        
                    }
//                    else if(ch[counter] != buffer){
//                        cout<<"985435"<<endl;
//                        //int1 = (int32_t)ch.size();
//                        write(STDOUT_FILENO, &int1, sizeof(int32_t));
//                        write(STDOUT_FILENO, &ch[0], 1);
//                        ch[counter] = buffer;
//                        int1 = 1;
//                        counter++;
//                     }
                else{
                    //cout<<"123"<<endl;
                   
                    if(buffer[0] != ch[j-1]){
                        ch[j] = buffer[0];
                        int1[j-1] = k;
                        j++;
                        k=1;
                    }else{
                        k++; //when all same chars
                    }
                    }
                }
                end=buffer[0];
                free(buffer);
                //free(ch);
                //free(int1);
                close(fd);
            }
        
            
  
        }
        ch[j]  = end; //the last char will not be stored above so to be stored here
        int1[j-1] = k;
        for(int m = 0; m < j; m++){
            write(STDOUT_FILENO, &int1[m], 4);
            write(STDOUT_FILENO, &ch[m], 1);
        }
        free(int1);
        free(ch);
        
    }
    
    return 0;
}

