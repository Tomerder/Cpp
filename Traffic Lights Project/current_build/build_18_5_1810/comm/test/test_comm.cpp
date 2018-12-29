// comm.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

//#include <CppUTest/TestHarness.h>
//#include <CppUTest/CommandLineTestRunner.h>

#include <iostream>
#include <cstring>

#include "comm.h"

#include "system.h"


using namespace std;


//
//TEST_GROUP(tg)
//{
//};
//
//TEST(tg, test_name)
//{
//    CommService(LOCAL_HOST, PORT);
//}
//
//
//int main(int argc, char** argv)
//{
//    return CommandLineTestRunner::RunAllTests(argc, argv);
//}
//

void HandleMsg(const Msg* _msg)
{
    if(_msg->m_header.m_type == SIMULATION_MSG)
    {
        cout << "Got message!!!" << endl;
    }
}



int main()
{

    Msg msg = {{EMULATION, SIMULATION_MSG, 0, sizeof(msg.m_header) + sizeof(SimulationMsg)}, {READY}};
    cout << msg.m_header.m_length << endl;

    CommService cs(IP_EMULATION, PORT_EMULATION);
    cs.AddPeer(OAM, IP_OAM, PORT_OAM);
    cs.SetMessageHandler(HandleMsg);
    cs.Send(OAM, msg);

    sleep(4);

    return 0;
}




