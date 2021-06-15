
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
    // see if the user passed in an argument
    if (argc < 2) {
        // it's already open
        cout<<"wunzip: file1 [file2 ...]"<<endl;
        exit(1);
    } else {
        int fd;
        int* int1 = (int*)malloc(sizeof(int) * INT_MAX); //make an int array to put the # of chars
        //int32_t int1;
        char* ch = (char*)malloc(sizeof(char) * INT_MAX); // put diff chars in
        //string ch;
        int ret;
        int j=0;
        for(int i = 1; i < argc; i++){
            fd = open(argv[i], O_RDONLY);
            if(fd < 0){
                cout<<"wzip: cannot open file"<<endl;
                exit(1);
            }
            else{
                int int2[4]; //#of integers; 4 bytes
                char ch1[1];// char in buffer, 1 byte; a group of 4byte int + 1 byte char
                while ((ret = read(fd, int2, 4)) > 0) { //read int in buffer first to convert it to dec
                    int1[j] = int2[0]; //put int in buffer into int1 array
                    ret = read(fd, ch1, 1); //read char in buffer, 1 byte per time
                    ch[j] = ch1[0]; //put char in buffer into ch array
                    j++;
                }
               
                close(fd);
            }
            
            
            
        }
        //write the converted stuff into output
        for(int i = 0; i < j; i++){
            for(int k = 0; k < int1[i]; k++){
                write(STDOUT_FILENO, &ch[i], 1);
            }
        }
        free(ch);
        free(int1);
          
        
    }
    
    return 0;

}
