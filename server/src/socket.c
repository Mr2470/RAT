// headers
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "socket.h"
// the socket library code

int making_socket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("socket is created\n");
    return sock;
}
int start_socket(int socket)
{
    printf("starting the socket\n");
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind failed");
        return -1;
    }
    listen(socket, 5);
    printf("socket is listening\n");
    while (1)
    {
        struct sockaddr_in client_addr = {0};
        socklen_t lenght = sizeof(client_addr);
        int client = accept(socket, (struct sockaddr *)&client_addr, &lenght);
        if (client == -1)
        {
            perror("accept failed");
            continue;
        }

        printf("%s\n", inet_ntoa(client_addr.sin_addr));

        char buffer[300];
        int bytes_recieved = recv(client, buffer, sizeof(buffer), 0);
        if (bytes_recieved > 0)
        {
            buffer[bytes_recieved] = '\0';
            printf("Message received: %s\n", buffer);
        }
        else if (bytes_recieved == 0)
        {
            printf("connection closed");
        }
        // else
        // {
        //     printf("there was an error contact mr2470 immediatelly");
        // }
    }

    return 0;
}