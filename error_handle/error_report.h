#ifndef _ERROR_REPORT_H_
#define _ERROR_REPORT_H_

void unix_error(char *msg);
void posix_error(int code, char *msg);
void gai_error(int code, char *msg);
void app_error(char *msg);

#endif