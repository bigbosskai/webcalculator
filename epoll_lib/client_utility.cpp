#include "client_utility.h"
//完成add功能
int add(int a, int b){
	return a+b;
}
//完成SUB功能
int sub(int a, int b){
	return a-b;
}

void wirtefile(){
	return;
}
//设置sockfd,pipefd非阻塞
int setnonblocking(int sockfd)
{
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)| O_NONBLOCK);
    return 0;
}

/**
  * @param epollfd: epoll handle
  * @param fd: socket descriptor
  * @param enable_et : enable_et = true, epoll use ET; otherwise LT
**/
void addfd( int epollfd, int fd, bool enable_et )
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;     //输入触发epoll-event
    if( enable_et )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    setnonblocking(fd);
 //   printf("fd added to epoll!\n\n");
}

//将服务器收到的clientfd的消息进行广播
int sendBroadcastmessage(int clientfd)
{

    char buf[BUF_SIZE], message[BUF_SIZE];
    //清零
    bzero(buf, BUF_SIZE);
    bzero(message, BUF_SIZE);

    printf("read from client(clientID = %d)\n", clientfd);
    int len = recv(clientfd, buf, BUF_SIZE, 0);

    if(len == 0)  // len = 0 client关闭了连接
    {
        close(clientfd);
        clients_list.remove(clientfd); //list删除fd
        printf("ClientID = %d closed.\n now there are %d client in the char room\n", clientfd, (int)clients_list.size());

    }
    else  //进行广播
    {
        if(clients_list.size() == 1) {
            send(clientfd, CAUTION, strlen(CAUTION), 0);
            return len;
        }

        sprintf(message, SERVER_MESSAGE, clientfd, buf);

        list<int>::iterator it;
        for(it = clients_list.begin(); it != clients_list.end(); ++it) {
           if(*it != clientfd){
                if( send(*it, message, BUF_SIZE, 0) < 0 ) { perror("error"); exit(-1);}
           }
        }
    }
    return len;
}
