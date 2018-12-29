// tcp_ip.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include "tcp_ip.h"

using namespace std;

#include <errno.h>
#include <cstring>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string>


//=== IP4 Address === 
Address::Address(const std::string& _ip, int _port)
{
    if(!this->SetAddress(_ip, _port))
    {
        this->ResetAddress();
    }
}



bool Address::SetAddress(std::string _ip, int _port)
{
    memset(this, 0, sizeof(sockaddr_in));
 
    if(inet_pton(AF_INET, _ip.c_str(), &sin_addr) != 1)
    {
        return false;
    }

    sin_family = AF_INET;
    sin_port = htons(_port);

    return true;
}


void Address::ResetAddress()
{
    memset(this, 0, sizeof(sockaddr_in));
    this->SetAddress(addr_default, port_default);
}

Address::operator std::string()
{
    char buff[INET_ADDRSTRLEN];
    return inet_ntop(AF_INET, &sin_addr, buff, INET_ADDRSTRLEN);
}


//============================================================

IPSocket::~IPSocket()
{
    if(m_socket != -1)
    {
        close(m_socket);
        m_socket = -1;
    }
}

int IPSocket::SetBlockingState(bool _state)
{
    int bits = fcntl(m_socket, F_GETFL);
    if(bits == -1)
    {
        return -1;
    }

    bits = (_state) ? bits & ~O_NONBLOCK : bits | O_NONBLOCK;

    int err = fcntl(m_socket, F_SETFL, bits);

    return err;
}

//int IPSocket::MakeNonBLocking()
//{
//    int bits = fcntl(m_socket, F_GETFD);
//    if(bits == -1)
//    {
//        return -1;
//    }
//
//    int err = fcntl(m_socket, F_SETFD, bits | O_NONBLOCK);
//    return err;
//}
//



int IPSocket::GetHandle() const
{
    return m_socket;
}



//============================================================

TCPconnection::
TCPconnection(int _sock) :
    IPSocket(_sock), m_buff(0) 
{}

TCPconnection::
~TCPconnection()
{
    if(m_buff)
    {
        delete m_buff;
        m_buff = 0;
    }
}


TCPconnection* 
TCPconnection::Create(int _sock)
{
    TCPconnection* tcpConn = new TCPconnection(_sock);

    return tcpConn;
}


TCPconnection* 
TCPconnection::Create(Address* _addr)
{
   int sock = socket(AF_INET, SOCK_STREAM, 0);
   if(sock == -1)
   {
       perror("Unable to create socket");
       return 0; 
   }

   int err = connect(sock, (const struct sockaddr*)_addr, sizeof(*_addr));
   if(err == -1)
   {
       perror("Failed to connect");
       return 0;
   }

   TCPconnection* tcpConn = new TCPconnection(sock);
   
   return tcpConn;
}


int TCPconnection::Close()
{
    if(m_socket == -1)
    {
        return -1;
    }

    int err = close(m_socket);
    m_socket = -1;
    return err;
}


int TCPconnection::Send(const char* _msgBuff, int _len)
{
    int nBytes = send(m_socket, _msgBuff, _len, 0);
    return nBytes;
}

int TCPconnection::Send(const std::string& _msg)
{
    int err = send(m_socket, _msg.c_str(), _msg.length(), 0);
    return err;
}

int TCPconnection::Recv(char* _buff, int _len)
{
    int nBytes = recv(m_socket, _buff, _len, 0);
    return nBytes;
}




//============================================================



TCPlistener::
TCPlistener(int _sock) : IPSocket(_sock)
{}

TCPlistener::
~TCPlistener()
{
    
}

TCPlistener* 
TCPlistener::
Create(Address* _addr, int _queueSize)
{
    int err = 0;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        return 0;
    }

    int optval = 1;
    err = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if(err)
    {
        close(sock);
        cout << "Unable to set listener socket to reusable" << endl;
        return 0;
    }

    err = bind(sock, (const struct sockaddr*)_addr, sizeof(sockaddr_in));
        if(err)
        {
            close(sock);
            return 0;
        }

    err = listen(sock, _queueSize);
        if(err)
        {
            close(sock);
            return 0;
        }

        TCPlistener* listener = new TCPlistener(sock);
        if(!listener)
        {
            close(sock);
        }

        return listener;
}

TCPconnection*
TCPlistener::
TryAccept()
{
    int sock = accept4(m_socket, (struct sockaddr*)&m_clientAddr, &m_lenAddr, SOCK_NONBLOCK);
    if(sock == -1)
    { if(   (errno == EAGAIN) || (errno == EINPROGRESS ) || (errno == EWOULDBLOCK))
        {
            return 0;
        }
        else
        {
            return 0;
        }
    }
    
    TCPconnection* tcpConn = TCPconnection::Create(sock);

    return tcpConn;
}

TCPconnection*
TCPlistener::
Accept()
{
	m_lenAddr = sizeof(m_clientAddr);
    int sock = accept(m_socket, (struct sockaddr*)&m_clientAddr, &m_lenAddr);
    if(sock == -1)
    {
    	printf("sock: %d ,  m_clientAddr %p, m_clientAddr %d", m_socket, (void*)&m_clientAddr, m_lenAddr);
    	perror("accept");
    	if(   (errno == EAGAIN) || (errno == EINPROGRESS ) || (errno == EWOULDBLOCK))
        {
            return 0;
        }
        else
        {
            return 0;
        }
    }
    
    TCPconnection* tcpConn = TCPconnection::Create(sock);

    return tcpConn;
}

