#ifndef _OPENFD_H_
#define _OPENFD_H_

#define LISTENQ  1024  /* Second argument to listen() */
int open_clientfd(char *hostname, char *port);
int open_listenfd(char *port);

#endif