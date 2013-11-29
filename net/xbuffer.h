#ifndef _XBUFFER_H_
#define _XBUFFER_H_

struct xbuffer
{
    char* bufAddr;
    int   usedLen;
    int   maxLen;
};

#endif