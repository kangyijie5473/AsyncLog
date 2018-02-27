//
// Created by kang on 17-11-15.
//

#include "LogStream.h"
#include "AsyncLogger.h"
#include <iostream>
#include <cstdio>
#include <zconf.h>

std::function<void(const char *, int)> LogStream::outputLogMessage = nullptr;

void toAsyncLogFile(const char *, int);
void testDataType(){

    std::string e = "hello\n";

    int t= 100;
    while(t--){
        LogStream logger;
        logger << e;
        if(t == 43)
            sleep(1);
    }

}
AsyncLogger testLogger("hello_log");


void toAsyncLogFile(const char *src, int len)
{
    testLogger.append(src, len);
}
void testThread()
{
    std::string e = "world\n";

    int t= 100;
    while(t--){
        LogStream logger;
        logger << e;
        if(t == 50)
            sleep(1);
    }

}


int main(void)
{
    LogStream::setOutputLogMessage(std::bind(toAsyncLogFile, std::placeholders::_1, std::placeholders::_2));
    testLogger.run();
    std::thread a(testThread);
    a.detach();

    //testDataType();

    sleep(4);
}