#include "log.h"

void log::init(const char* _fileName)
{
	if (_fileName == NULL)
	{
		m_fileHandle = stdout;
		return ;
	}
}

void log::debug(const char* _format, ...)
{
	va_list arg;
	va_start(arg, _format);
	vfprintf(m_fileHandle,_format,  arg);
	va_end(arg);
}
