/*
 * > File Name: LogBuffer.cpp
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年11月14日 星期二 22时34分00秒
 */


#include "LogBuffer.h"
#include <cstring>
bool LogBuffer::append(const char *str, int len)
{
    if(len > this->free_size())
        return false;
    else
        memcpy(&buffer_[now_index_], str, len);

    now_index_ += len;
    return true;
}
int LogBuffer::free_size() const
{
    return buffer_max_size - now_index_ ;
}
void LogBuffer::clear()
{
    now_index_ = 0;
}
