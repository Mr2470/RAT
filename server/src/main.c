// headers

#include <stdio.h>
#include <stdlib.h>

#include "socket.h"
// application

int main()
{
    printf("server is starting : \n");
    int server = making_socket();
    printf("%d\n", server);
    start_socket(server);
    return 0;
}