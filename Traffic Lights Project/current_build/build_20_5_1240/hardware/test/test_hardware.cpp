// test_hardware.cpp
//
//	unit tests 
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <iostream>     // for debug prints

#include "hardware.h"

#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

using namespace std;
using namespace hw;

//=== hw_read_write =======================================
TEST_GROUP(hw_read_write)
{
};


TEST(hw_read_write, write_and_read)
{

    Hardware::Write(128, 128);

    CHECK(Hardware::Read(128) == 128);

    Hardware::Write(0, 256);

    CHECK(Hardware::Read(0) == 256);

}

TEST(hw_read_write, test_reset)
{
    for(uint i = 0; i < MAX_HARDWARE; ++i)
    {
        Hardware::Write(i, i+1);
    }

    Hardware::Reset();

    for(uint i = 0; i < MAX_HARDWARE; ++i)
    {
        CHECK(Hardware::Read(i) == 0);
    }
    
}

//=== registers ===========================================

enum Registers
{
    CAR_SENSOR_1,
    CAR_SENSOR_2
};

const uint CAR_SENSOR_1_REGISTER_ADDR = 0x128;
const uint CAR_SENSOR_2_REGISTER_ADDR = 0x129;

TEST_GROUP(registers)
{
};



TEST(registers, map_to_address_and_reset)
{
    for(uint i = 0; i < MAX_DEVICES; ++i)
    {
        Register::MapToAddress(i, i);
        Register::WriteWithShadow(i, i);
    }


    for(uint i = 0; i < MAX_DEVICES; ++i)
    {
        CHECK(Register::ReadShadow(i) == i);
    }

    Register::Reset();

    for(uint i = 0; i < MAX_DEVICES; ++i)
    {
        CHECK(Register::ReadShadow(i) == 0);
    }
}

TEST(registers, write_and_read)
{
    Register::Reset();
    Hardware::Reset();

    Register::MapToAddress(CAR_SENSOR_1, CAR_SENSOR_1_REGISTER_ADDR);

    Register::WriteWithShadow(CAR_SENSOR_1, 256);
    
    CHECK(Register::ReadShadow(CAR_SENSOR_1) == 256);
    CHECK(Hardware::Read(CAR_SENSOR_1_REGISTER_ADDR) == 256);
}

//=== Interrupt ===========================================

void ISR_dummy()
{
    cout << "ISR_dummy()" << endl;
}

TEST_GROUP(interrupt)
{
};

TEST(interrupt, bind)
{
    Interrupt::Bind(ISR_dummy, 1);
    
}



//=========================================================
int main(int argc, char** argv)
{

    return CommandLineTestRunner::RunAllTests(argc, argv);

}
