/*
 * > File Name: LogStream.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年11月14日 星期二 22时22分03秒
 */
#include "LogStream.h"
#include <algorithm>
#include <vector>

const int MAX_INT_LEGNTH = 30;
LogStream& LogStream::operator<<(bool b) {
    buffer_.append(b ? "T" : "F", 1);
    return *this;
}
LogStream& LogStream::operator<<(const char c)
{
    buffer_.append(&c, 1);
    return *this;
}
LogStream& LogStream::operator<<(const char *str)
{
    buffer_.append(str, strlen(str));
    return *this;
}

/* Integer to string */
static const char digits[19] = {'9', '8', '7', '6', '5', '4', '3', '2', '1', '0',
                                '1', '2', '3', '4', '5', '6', '7', '8', '9'};
static const char *zero = digits + 9;
template <typename T>
int LogStream::getIntegerString_(char *buf, T value) {
    char *p = buf;
    do{
        int i = value % 10;
        *p++ = zero[i];
        value /= 10;
    }while (value);
    if(value < 0)
        *p++ = '-';
    *p = '\0';
    std::reverse(buf, p);
    return p - buf;
}

/* get format Integer and append buffer */
template <typename T>
void LogStream::appendFormatInteger_(T i)
{
    char buf[MAX_INT_LEGNTH];
    int len = getIntegerString_(buf, i);
    buffer_.append(buf, len);
}


LogStream& LogStream::operator<<(unsigned int i)
{
    appendFormatInteger_(i);
    return *this;
}
LogStream& LogStream::operator<<(int i)
{
    appendFormatInteger_(i);
    return *this;
}
LogStream& LogStream::operator<<(unsigned long i)
{
    appendFormatInteger_(i);
    return *this;
}
LogStream& LogStream::operator<<(long i)
{
    appendFormatInteger_(i);
    return *this;
}
LogStream& LogStream::operator<<(long long i)
{
    appendFormatInteger_(i);
    return *this;
}
LogStream& LogStream::operator<<(unsigned long long i)
{
    appendFormatInteger_(i);
    return *this;
}
LogStream& LogStream::operator<<(unsigned short i)
{
    appendFormatInteger_(i);
    return *this;
}
LogStream& LogStream::operator<<(short i)
{
    appendFormatInteger_(i);
    return *this;
}

LogStream& LogStream::operator<<(double i)
{
    // todo:float
}

LogStream& LogStream::operator<<(float i)
{
    // todo:float
}
LogStream& LogStream::operator<<(const LogBuffer& logbuffer)
{
    buffer_.append(logbuffer.data(), LogBuffer::buffer_max_size - logbuffer.free_size());
    return *this;
}
LogStream& LogStream::operator<<(const std::string& str)
{
    buffer_.append(str.c_str(), str.size());
    return *this;
}
void LogStream::setOutputLogMessage(std::function<void(const char *, int)>&& out)
{
    LogStream::outputLogMessage = out;
}
LogStream::~LogStream()
{
    outputLogMessage(buffer_.data(), LogBuffer::buffer_max_size - buffer_.free_size());
}