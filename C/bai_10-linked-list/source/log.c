#include "log.h"
#include <stdio.h>

void list_log(ListStatus e, const char *msg)
{
    const char *name = "UNKNOWN";
    switch (e)
    {
    case LIST_OK:
        name = "OK";
        break;
    case LIST_ALLOC_FAILED:
        name = "ALLOC_FAILED";
        break;
    case LIST_EMPTY:
        name = "EMPTY_LIST";
        break;
    case LIST_OUT_OF_RANGE:
        name = "OUT_OF_RANGE";
        break;
    case LIST_NULL:
        name = "NULL_ARG";
        break;
    default:
        break;
    }

    if (msg)
        fprintf(stderr, "[LIST][%s] %s\n", name, msg);
    else
        fprintf(stderr, "[LIST][%s]\n", name);
}
