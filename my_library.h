#include <poll.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <time.h>

/*input function that doesn't wait if stdin empty and
switches off buffering*/
void catch_input(char *buf, int buf_len) 
{
    struct pollfd fds[1];
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    int timeout = 0;
    int number_of_fds = 1;
    //switches off input buffering
    system("/bin/stty raw");
    while(poll(fds, number_of_fds, timeout)) 
    {
        memset(buf, '\0', buf_len);
        read(0, buf, buf_len);
    }
    //switches input buffering back on again
    system("/bin/stty -raw");
}

int primeNum(int num) 
{
    bool retVal = true;
    for(int i = 2; i <= num / 2; i++) 
    {
        if(num % i == 0) 
        {
            retVal = false;
            break;
        }
    }
    return retVal;
}

//euclidean algorithm