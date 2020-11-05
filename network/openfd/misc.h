#ifndef _MISC_H_
#define _MISC_H_

#include <unistd.h>
#include <netinet/ip.h>
#include <stdio.h>
#include "lib/rio.h"

#define	MAXLINE	 8192

int Open_listenfd(char *port); 
int Open_clientfd(char *hostname, char *port);

ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen); 
void Rio_writen(int fd, void *usrbuf, size_t n); 
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, 
                 size_t hostlen, char *serv, size_t servlen, int flags);
void Close(int fd); 
char *Fgets(char *ptr, int n, FILE *stream);
void Fputs(const char *ptr, FILE *stream);


#endif