#ifndef _K2D_LOG_H_
#define _K2D_LOG_H_

#include <string>
#include <fstream>
#include "K2D_Tool.h"
#include "singleton.h"

#define K2D_LOG_FILE "K2D_log.txt"

enum
{
	K2D_ERROR	= 0,
	K2D_OK		= 1,
	K2D_INFO	= 2
};

class K2D_Log: public singleton<K2D_Log>
{
	friend class singleton<K2D_Log>;
public:
	void Open (char* szLogFile)
	{
		m_Stream.open (szLogFile);
		Log (" -- Start logging (%s)--\n", K2D_Tool::Date("h:i:s").c_str());
	}
	void Log (char* format, ...)
	{
		static const int MAX_BUFF_SIZE = 2048;
		static char buffer[MAX_BUFF_SIZE];
		va_list args;

		va_start(args, format);
			vsprintf(buffer, format, args);
		va_end(args);

		m_Stream << buffer << '\n';
		m_Stream.flush ();		
	}
	void Log (int type, char* format, ...)
	{
		switch (type){
		case K2D_ERROR:
			m_Stream << "<!> ";
			break;
		case K2D_OK:
			m_Stream << "<-> ";
			break;
		case K2D_INFO:
		default:
			break;
		}
		static const int MAX_BUFF_SIZE = 2048;
		static char buffer[MAX_BUFF_SIZE];
		va_list args;

		va_start(args, format);
			vsprintf(buffer, format, args);
		va_end(args);

		m_Stream << buffer << '\n';
		m_Stream.flush ();
	}
	void Close ()
	{
		Log ("\n -- Closing log (%s)--", K2D_Tool::Date("h:i:s").c_str());
		m_Stream.close ();

	}
private:
	K2D_Log (){}
	std::ofstream m_Stream;

};

#endif