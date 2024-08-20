#include "LogHandler.h"

#include <iostream>
#include <cstdarg>
#include <vector>

LogHandler::LogHandler()
{
#ifndef CF_DEBUG_MODE
	m_file.open("RuntimeErrorLog.txt", std::ios::trunc);
#endif
}

void LogHandler::OutputLog(std::string_view format, ...)
{
	va_list args;
	va_start(args, format);

#ifdef CF_DEBUG_MODE
	this->OutputLogToConsole(format, args);
#else
	this->OutputLogToFile(format, args);
#endif

	va_end(args);
}

#ifdef CF_DEBUG_MODE
void LogHandler::OutputLogToConsole(std::string_view format, va_list args)
{
	std::vprintf(format.data(), args);
}
#else
void LogHandler::OutputLogToFile(std::string_view format, va_list args)
{
	const int requiredBufferSize = std::vsnprintf(nullptr, 0, format.data(), args) + 1;
	std::vector<char> buffer(requiredBufferSize);
	std::vsprintf(buffer.data(), format.data(), args);
	m_file << buffer.data();
}
#endif

LogHandler& LogHandler::GetInstance()
{
	static LogHandler instance;
	return instance;
}
