#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define SERV_PORT 9527
//#define SERV_ADDR "127.0.0.1"

int main()
{
    int data_fd, count = 10;
    struct sockaddr_in server_addr;
    //char *server_ip = "127.0.0.1";
    char buff[1024], read_cnt;
    //socklen_t client_addr_len = sizeof(client_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);

    if ((data_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket fail");
        return -1;
    }

    if (connect(data_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect fail");
        close(data_fd);
        return -1;
    }

    while (count--) {
        write(data_fd, "hello\n", 6);
        read_cnt = read(data_fd, buff, sizeof(buff));
        write(STDOUT_FILENO, buff, read_cnt);
        sleep(1);
    }
    close(data_fd);
    
    return 0;
}