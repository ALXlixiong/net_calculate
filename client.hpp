#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__ 

#include "comm.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>

class Client 
{
  private:
    int _sock;
    int _port;
    std::string _ip;
  public:
    Client(const int &port,const std::string ip)
      :_port(port)
      ,_ip(ip)
      ,_sock(-1)
  {}
    ~Client()
    {
      close(_sock);
    }
    void NumberFun(Request_t &rq)
    {
      Response_t rsq;
      std::cout<<"请输入操作数<x,y>";
      std::cin>>rq.x>>rq.y;
      std::cout<<"请输入操作码《+ - * / ^ %》"<<std::endl;
      std::cout<<"Please enter>>";
      std::cin>>rq.op;
      send(_sock,&rq,sizeof(rq),0);
      recv(_sock,&rsq,sizeof(rsq),0);
      if(rsq.status == 0)
        std::cout<<"result = "<<rsq.result<<std::endl;
      else if(rsq.status == -1)
        std::cout<<"input error"<<std::endl;
      std::cout<<std::endl;
    }
    void InputFun()
    {
      ;
    }
    void Run()
    {
      std::cout<<"--注意:输入操作数使用逗号间隔---"<<std::endl;
      for(;;)
      {
        Request_t rq;
        std::cout<<"-----请输入计算类型对应数字-----"<<std::endl;
        std::cout<<"--------------------------------"<<std::endl;
        std::cout<<"1:日期计算 2:数字计算 3:进制转化"<<std::endl;
        std::cout<<"--------------------------------"<<std::endl;
        std::cout<<"Please enter>>";
        std::cin>>rq.cal_kind;
        //fflush(stdout);
        //sleep(1);
        //InputFun(); 
        switch(rq.cal_kind)
        {
          case 1:
            break;
          case 2:
            NumberFun(rq);
            break;
          case 3:
            break;
          default:
            std::cerr<<"input error"<<std::endl;
            break;
        }
        std::cin.clear();
        std::cin.sync();
        std::cin.ignore(1024,'\n');
      }
    }
    void ClientInit()
    {
      _sock = socket(AF_INET,SOCK_STREAM,0);
      if(_sock<0)
      {
        std::cerr<<"client socket error"<<std::endl;
        exit(1);
      }
      struct sockaddr_in client;
      bzero(&client,sizeof(client));
      client.sin_family = AF_INET;
      client.sin_port = htons(_port);
      client.sin_addr.s_addr = inet_addr(_ip.c_str());
       
      int ret = connect(_sock,(struct sockaddr *)&client,sizeof(client));
      if(ret<0)
      {
        std::cerr<<"client connect error"<<std::endl;
        close(_sock);
        exit(1);
      }
      std::cout<<"connect success..."<<std::endl;
    }
};

#endif  //__CLIENT_HPP__
