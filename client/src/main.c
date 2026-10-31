#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
    int client = socket(AF_INET, SOCK_STREAM, 0);

    if (client == -1)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect");
        close(client);
        return 1;
    }

    char message[] = "Hello Arta!";

    if (send(client, message, strlen(message), 0) == -1)
        perror("send");
    else
        printf("Message sent successfully!\n");

    close(client);

    return 0;
}
