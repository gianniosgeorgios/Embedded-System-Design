#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
//#include <termios.h>

#define BUFF_SIZE 64
int main(void)
{
    //struct termios tio;
    int fd;
    char input[BUFF_SIZE], output[BUFF_SIZE];
    const char device[] = "/dev/pts/1";

    printf("Please give a string to send to guest:\n");
    fgets(input, BUFF_SIZE, stdin);
    
    /* Open the device for reading and writing and not as controlling tty
       because we don't want to get killed if linenoise sends CTRL-C. */

    fd = open(device, O_RDWR | O_NOCTTY);
    
    if (fd == -1) {
        printf("Failed to open port\n");
        return 1;
    }
    
    /* Find flags for the guest.s (We ran this in the guest)
     
    tcgetattr(fd, &tio); (save current serial port settings)
    printf("iflag: %x, oflag: %x, lflag: %x cflag: %x\n", tio.c_iflag, tio.c_oflag, tio.c_lflag, tio.c_cflag); (flags for options to guest)
    
    */
    
    write(fd, input, BUFF_SIZE);
    
    while (read(fd, output, BUFF_SIZE) <= 0);
    
    printf("The most frequent character is %c and it appeared %d times. \n", output[0], output[1]);
    
    close(fd);
    return 0;
}
