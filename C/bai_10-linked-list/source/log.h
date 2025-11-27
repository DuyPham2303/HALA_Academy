#ifndef LOG_H
#define LOG_H

#include "list.h"

/* Debug / error helper functions (implemented in debug.c) */
int list_setjmp(void);                          /* wrapper for setjmp(list_env) */
void list_log(ListStatus e, const char *msg);   /* chuỗi msg mô tả lỗi do user thiết kế */
void list_throw(ListStatus e, const char *msg); /* log chuỗi msg*/

#endif