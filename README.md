### 一个异步日志库
### 简介
使用C++11实现，可跨平台的异步日志库。将日志以文件的形式持久化到本地磁盘上。   
### Why异步
采用同步写的方式会导致程序阻塞在磁盘IO，整个程序的运行效率会大大降低。  
### 跨平台特性
多线程部分采用C++11的`<thread>` `<mutex>` 等实现，保证程序的可移植性，采用CMake构建项目。  
### 实现原理
分为前台线程和后台线程。前台线程相当于生产者--产生日志，后台线程相当于消费者--持久化日志。  
当程序写日志时，首先放到前台线程的缓冲区内，当缓冲区满或者同步时间到达，将日志缓冲区通过*移动*的方式交给后台线程，后台线程负责将缓冲区中的日志写入磁盘。

核心为LogBuffer LogStream AsyncLogger。
AsyncLogger 实现前台线程与后台线程的同步，后台线程写入日志文件。  
LogStream 提供格式化的日志写入，可控制日志输出形式（可根据需要自定义，如写入到socket等）。  
LogBuffer 自定义缓冲区。  

