#include "rio.h"
#define MAXLINE 256
int main()
{
    int n;
    rio_t rio;
    char buf[MAXLINE];
    rio_readinitb(&rio, STDIN_FILENO);
    while((n = rio_readlineb(&rio, buf, MAXLINE)) != 0)
        rio_writen(STDOUT_FILENO, buf, n);
    return 0;
}