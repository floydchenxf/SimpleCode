#ifndef _LOG_H_
#define _LOG_H_

#include "compact.h"

class log
{
public:
	void init(const char* _fileName = NULL);
	void debug(const char* _format, ...);
    void trace(const char* _format, ...);
    void error(const char* _format, ...);

private:
	FILE* m_fileHandle;
};

static log gs_log;

#endif
