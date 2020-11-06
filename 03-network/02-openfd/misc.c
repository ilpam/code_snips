
#include "lib/openfd.h"
#include "lib/rio.h"
#include "lib/error_report.h"
#include "misc.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>

/* here we warp some useful function */
int Open_listenfd(char *port) 
{
    int rc;
    if ((rc = open_listenfd(port)) < 0)
	    unix_error("Open_listenfd error");
    return rc;
}

int Open_clientfd(char *hostname, char *port) 
{
    int rc;
    if ((rc = open_clientfd(hostname, port)) < 0) 
	    unix_error("Open_clientfd error");
    return rc;
}

ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) 
{
    ssize_t rc;

    if ((rc = rio_readlineb(rp, usrbuf, maxlen)) < 0)
	    unix_error("Rio_readlineb error");
    return rc;
} 

void Rio_writen(int fd, void *usrbuf, size_t n) 
{
    if (rio_writen(fd, usrbuf, n) != n)
        unix_error("Rio_writen error");
}

int Accept(int s, struct sockaddr *addr, socklen_t *addrlen) 
{
    int rc;
    if ((rc = accept(s, addr, addrlen)) < 0)
	unix_error("Accept error");
    return rc;
}

void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, 
                 size_t hostlen, char *serv, size_t servlen, int flags)
{
    int rc;
    if ((rc = getnameinfo(sa, salen, host, hostlen, serv, 
                          servlen, flags)) != 0) 
        gai_error(rc, "Getnameinfo error");
}

void Close(int fd) 
{
    int rc;
    if ((rc = close(fd)) < 0)
	unix_error("Close error");
}

char *Fgets(char *ptr, int n, FILE *stream) 
{
    char *rptr;
    if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream))
	    app_error("Fgets error");
    return rptr;
}

void Fputs(const char *ptr, FILE *stream) 
{
    if (fputs(ptr, stream) == EOF)
	    unix_error("Fputs error");
}