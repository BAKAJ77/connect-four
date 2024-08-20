#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include <string>

#ifndef CF_DEBUG_MODE
#include <fstream>
#endif

class LogHandler
{
public:
	~LogHandler() = default;

	void OutputLog(std::string_view format, ...);

	static LogHandler& GetInstance();
private:
	LogHandler();


#ifdef CF_DEBUG_MODE
	void OutputLogToConsole(std::string_view format, va_list args);
#else
	void OutputLogToFile(std::string_view format, va_list args);
#endif
private:
#ifndef CF_DEBUG_MODE
	std::ofstream m_file;
#endif
};

#endif
