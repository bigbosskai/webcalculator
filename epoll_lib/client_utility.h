//client_utility.h
#ifndef CLIENT_UTILITY_H_INCLUDED
#define CLIENT_UTILITY_H_INCLUDED

#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

// ip
#define SERVER_IP "127.0.0.1"
#define CLIENT_IP "127.0.0.1"

// server port
#define SERVER_PORT 9999

//epoll 支持的最大并发量
#define EPOLL_SIZE 5000

//message buffer size
#define BUF_SIZE 0xFFFF

#define SERVER_WELCOME "Welcome you join  to the chat room! Your chat ID is: Client #%d"

#define SERVER_MESSAGE "ClientID %d say >> %s"

// exit
#define EXIT "EXIT"

#define CAUTION "There is only one int the char room!"

// 选用list方便删除sockfd
extern list<int> clients_list;

//设置sockfd,pipefd非阻塞
int setnonblocking(int sockfd);

/**
  * @param epollfd: epoll handle
  * @param fd: socket descriptor
  * @param enable_et : enable_et = true, epoll use ET; otherwise LT
**/
void addfd( int epollfd, int fd, bool enable_et );

//将服务器收到的clientfd的消息进行广播
int sendBroadcastmessage(int clientfd);

#endif // CLIENT_UTILITY_H_INCLUDED

