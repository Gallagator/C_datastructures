#include "strdup.h"

#include <malloc.h>
#include <string.h>


//#if _XOPEN_SOURCE >= 500 || _POSIX_C_SOURCE >= 200809L || _BSD_SOURCE || _SVID_SOURCE   

char* strdup(const char* s)
{
    char* p = malloc(strlen(s) + 1);
    if (p != NULL) 
    {
        strcpy(p, s);
    }
    return p;
}

//#endif
