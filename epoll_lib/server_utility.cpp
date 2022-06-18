#include "server_utility.h"

//增加mul功能
int mul(int a,int b)
{
		return a / b;
}

// 从"num1 num2"格式中解析出num1+num2的结果
int getAddResult(char buf[], int len){
// int getAddResult(char *buf, int len){
    int num1=0, num2=0, index=-1;
    for(int i=0;i<len;i++){
        if(buf[i]==' '){
            index = i;
            break;
        }
    }
    // std::cout << "index = "  << index << std::endl;
    for(int i = index-1;i>=0;i--){
        num1=num1+(buf[i]-'0')*pow(10, index-1-i); //// buf[i]是字符对应的ascii码
    }
    // std:: cout << "num1 done!" << std::endl;
    for(int i = len-1;i>index;i--){
        num2=num2+(buf[i]-'0')*pow(10, len-1-i);  
    }
    return num1+num2;
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
    ev.data.fd = fd; ////设置与要处理的事件相关的文件描述符
    ev.events = EPOLLIN;     //输入触发epoll-event ////设置要处理的事件类型
    if( enable_et )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);////注册epoll事件
    setnonblocking(fd);
 //   printf("fd added to epoll!\n\n");
}

//将服务器收到的clientfd的消息进行广播
int sendBroadcastmessage(int clientfd)
{
    
    char buf[BUF_SIZE], message[BUF_SIZE];
    // char message[BUF_SIZE];
    int result;
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
        // if(clients_list.size() == 1) {
        //     send(clientfd, CAUTION, strlen(CAUTION), 0);
        //     return len;
        // }
        
        // sprintf(message, SERVER_MESSAGE, clientfd, buf);
        // buf是发送来的信息 char[] 比如44 55xxx 以‘\0’结束？
        int res = getAddResult(buf,strlen(buf));
        // printf("the res is : %d", res);

        sprintf(message, SERVER_MESSAGE, clientfd, res);
        if( send(clientfd, message, BUF_SIZE, 0) < 0 ) { perror("error"); exit(-1);}
         
        // 我们与之相反，只广播给clientfd ？？？
        // list<int>::iterator it;
        // for(it = clients_list.begin(); it != clients_list.end(); ++it) {
        //    if(*it != clientfd){
        //         if( send(*it, message, BUF_SIZE, 0) < 0 ) { perror("error"); exit(-1);}
        //    }
        // }

    }
    return len;
}
