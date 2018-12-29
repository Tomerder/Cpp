// tcp_ip.h
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#ifndef __TCP_IP_H__
#define __TCP_IP_H__

#include <arpa/inet.h>  // ???TODO

#include <sys/types.h>  // ???TODO
#include <sys/socket.h> // for socket

#include <string>       // for std::string

    
// default buffer size of the Connection class
const int g_buffSize = 256; 

const std::string addr_default = "127.0.0.1";
const int port_default = 80;

//=== IP4 Address ===
struct Address : public sockaddr_in
{
    Address(const std::string& _ip = addr_default, int _port = port_default);
    bool SetAddress(std::string _ip, int _port);
    void ResetAddress();
    operator std::string();
};


//=== IPSocket ===
class IPSocket
{
public:

    IPSocket(int _sock)
        :m_socket(_sock)
    {};

    virtual ~IPSocket() = 0;

    int SetBlockingState(bool _state);

    int GetHandle() const;

protected:

    int m_socket;
};


class TCPconnection : public IPSocket
{
    public:

        static TCPconnection* Create(int _sock);
        static TCPconnection* Create(Address* _addr);

        virtual ~TCPconnection();


        int Close();

        // returns number of bytes sent
        int Send(const char* _msgBuff, int _len);
        int Send(const std::string& _msg);

        // returns number of bytes received 
        int Recv(char* _buff, int _len);

    private:

        explicit TCPconnection(int _sock);

        char* m_buff;
};


class TCPlistener : public IPSocket
{
    public:

        virtual ~TCPlistener();

        static TCPlistener* Create(Address* _addr, int _queueSize);
    
        TCPconnection* TryAccept();

        TCPconnection* Accept();

    private:
        TCPlistener(int _sock);

        Address m_clientAddr;
        socklen_t m_lenAddr;

};





#endif //__TCP_IP_H__
