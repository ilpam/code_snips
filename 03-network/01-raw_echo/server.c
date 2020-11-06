#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define SERV_PORT 9527

/*
* this is a simple echo server example, without any other library
*/

int main()
{
    int link_fd, data_fd;
    struct sockaddr_in server_addr, client_addr;
    char buff[1024], read_cnt;
    socklen_t client_addr_len = sizeof(client_addr);

    /* prepare server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((link_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("create listen fd fail");
        return -1;
    }
    
    if (bind(link_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind error");
        close(link_fd);
        return -1;
    }

    if (listen(link_fd, 5) == -1) {
        perror("listen error\n");
        close(link_fd);
        return -1;
    }

    printf("waiting for connect...\n");
    if ((data_fd = accept(link_fd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
        perror("link fail\n");
        close(link_fd);
        return -1;
    }

    printf("established..\n");
    
    while ((read_cnt = read(data_fd, buff, sizeof(buff))) != EOF) {
        write(STDOUT_FILENO, buff, read_cnt);
        for (int i = 0; i < read_cnt; ++i) {
            buff[i] = toupper(buff[i]);
        }
        write(data_fd, buff, read_cnt);
    }

    close(link_fd);
    close(data_fd);
    return 0;
}