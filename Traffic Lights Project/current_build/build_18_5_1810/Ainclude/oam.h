// oam.h
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#ifndef __OAM_H__
#define __OAM_H__

#include "system.h"
#include "comm.h"



class OAM_t
{
public:
    explicit OAM_t();
    ~OAM_t();

    void Start();

private:

    static void MsgHandler(const Msg* _msg);
    static OAM_t* m_instance;

    CommService* m_comm;
    bool m_running;


}; // class OAM_t



#endif //__OAM_H__
