#include <errno.h>
#include <string.h>
//#include <stdio.h>
#include "rio.h"

void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

/*
* this function is user-level buffered read,
* it has the same semantic as system call read()
*/
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;

    while (rp->rio_cnt <= 0) {                            /* user buf is empty */
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        if (rp->rio_cnt < 0) {
            if (errno != EINTR)                           /* interrupted by signal */
                return -1;
        } else if (rp->rio_cnt == 0) {                    /* get EOF */
            return 0;
        } else {
            rp->rio_bufptr = rp->rio_buf;
        }
    }

    cnt = (rp->rio_cnt < n) ? rp->rio_cnt : n;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

/*
*   this function is used to read a text line
*/
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    int n, rc;
    char c, *bufp = usrbuf;

    for (n = 1; n < maxlen; n++) {
        if ((rc = rio_read(rp, &c, 1)) == 1) {
            *bufp++ = c;
            if (c == '\n') {
                n++;
                break;
            }
        } else if (rc == 0) {           /* get EOF */
            if (n == 1)
                return 0;
            else 
                break;
        } else {
            return -1;
        }
    }
    *bufp = 0;
    //printf("return %d\n", n-1);
    return n-1;
}

/*
* this function is the same as rio_readn(), but it has user-level buffer
*/
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;
    while (nleft > 0) {
        if (nread = rio_read(rp, bufp, nleft) < 0) {
            return -1;             /* other error, let user check this */
        } else if (nread == 0) {       /* meet EOF, return total read count */
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);                /* always >= 0, final read count */
}

/*
 * user expect to read n byte from fd, 
 * if EOF is not meed, this function will never return
 * 
 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;
    while (nleft > 0) {
        if (nread = read(fd, bufp, nleft) < 0) {
            if (errno == EINTR) {
                nread = 0;             /* interrupted by singal, just read again */
            } else {
                return -1;             /* other error, let user check this */
            }
        } else if (nread == 0) {       /* meet EOF, return total read count */
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);                /* always >= 0, final read count */
}

/*
 * user expect to write n byte to fd, 
 * just return for 2 case: 1.error happen; 2.write finish
 * 
 */
ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;
    while (nleft > 0) {
        if ((nwritten = write(fd, bufp, nleft)) <= 0) {
            if (errno == EINTR) {
                nwritten = 0;          /* interrupted by singal, just write again */
            } else {
                return -1;             /* other error, let user check this */
            }
        }  
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;                         /* always return n */
}