#include "error_report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void posix_error(int code, char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}
void gai_error(int code, char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, gai_strerror(code));
    exit(0);
}
void app_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}