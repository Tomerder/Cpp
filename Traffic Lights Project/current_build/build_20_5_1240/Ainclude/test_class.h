// test_class.h
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on: 2014-04-08
//	Last modified:

#include <iostream>
#include <vector>
#include <string>


using namespace std;


struct Base
{
    Base(bool print = 0):m_dtorPrint(print), m_data(0), m_otherData(0){}
    virtual ~Base(){if(m_dtorPrint){cout << "Base::~Base" << '\n';}}

    bool m_dtorPrint;
    int m_data;
    int m_otherData;
};

struct Derived : public Base
{
    virtual ~Derived(){if(m_dtorPrint){cout << "Derived::~Derived" << '\n';}}

};


struct TestCase
{
    TestCase(string _name)
        :m_testName(_name), m_pass(true)
    {};

    virtual ~TestCase()
    {
        cout << m_testName << ": ";

        if(m_pass)
        {cout << "PASS";}
        else
        {cout << "FAIL";}
        cout << '\n';
    }


    void CheckTrue(bool _cond){m_pass |= _cond;}
    void CheckFalse(bool _cond){m_pass |= !_cond;}


    template <class A, class B>
    void CheckEqual(A a, B b){m_pass |= (a == b);}

    template <class A, class B>
    void CheckNotEqual(A a, B b){m_pass |= !(a == b);}


// Data members
    private:

    string m_testName;

    TestCase* m_parent;

    bool m_pass;
};
