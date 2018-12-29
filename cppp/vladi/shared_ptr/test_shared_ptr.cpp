// test_shared_ptr.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <iostream>
#include <vector>

#include "shared_ptr.h"

using namespace std;
using namespace m10;

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


struct TestCtor : public TestCase
{
    // Expect default ctor to create object which evaluates to false
    void DefaultCtor()
    {
        shared_ptr<int> sp;
        CheckFalse(sp);
    }

    void CTORfromIntPtr()
    {
        shared_ptr<int> sp(new int(5));
        CheckTrue(sp);
        CheckEqual(*sp, 5);
    }

    void CopyCTOR()
    {
        shared_ptr<int> sp(new int(5));
        shared_ptr<int> sp2(sp);
        CheckEqual(sp, sp2);
        CheckEqual(*sp, *sp2);
    }

    void BaseCTORfromDerived()
    {
        shared_ptr<Derived> spd(new Derived);
        shared_ptr<Base> spb(spd);
        CheckEqual(spd, spb);
    }
    

    TestCtor():TestCase("CTOR")
    {
        DefaultCtor();
        CTORfromIntPtr();
        CopyCTOR();
        BaseCTORfromDerived();
    }
};


struct TestGetCPtr : public TestCase
{
    void GetCptr()
    {
        shared_ptr<int> sp(new int(5));
        int * ip = sp.GetCPtr();
        *ip = 1;
        CheckEqual(*sp, 1);
    }
    
    void GetConstCptr()
    {
        const shared_ptr<int> sp(new int(5));
        const int * ip = sp.GetCPtr();
        CheckEqual(ip, sp); 
    }


    TestGetCPtr() : TestCase("GetCptr")
    {
        GetCptr();
        GetConstCptr();
    }
};


struct TestConversionOps : public TestCase
{

    void OpBool()
    {
        shared_ptr<int> spz;
        shared_ptr<int> sp(new int(5));
        CheckTrue(bool(sp));
        CheckFalse(bool(spz));
        CheckTrue(sp);
        CheckFalse(!sp);
        CheckFalse(spz);
        CheckTrue(!spz);

//        shared_ptr<int>::Bool bp = (Bool)sp;

        //int i = spz * 8 + 5;
        //cout << i << endl;
    }

    void OpStar()
    {
        int * ip = new int(5);
        shared_ptr<int> sp(ip);
        CheckEqual(ip, sp);
        CheckEqual(ip, (int *)sp);
        
    }

    void ConstOpStar()
    {
        const int *cip = new int(5);
        shared_ptr<const int> scip(cip);
        shared_ptr<int> sip(new int(10));
        shared_ptr<int> sip2;
        scip = sip;
        delete cip;
        // sip2 = scip; // won't compile!
    }

    TestConversionOps() : TestCase("Conversion Operators")
    {
        OpBool();
        OpStar();
        ConstOpStar();
    }
};

struct TestOpArrow : public TestCase
{
    void OpArrow()
    {
        shared_ptr<Base> sp(new Base);
        CheckEqual(sp->m_data, 0);
        sp->m_data = 5;
        CheckEqual(sp->m_data, 5);
    }

    void OpArrowConst()
    {
        const shared_ptr<Base> sp(new Base);
        CheckEqual(sp->m_data, 0);
        int i = sp->m_data;
        i++;

        shared_ptr<Base> sp2(new Base);
        // Won't compile!
        //sp = sp2;
    }

    TestOpArrow(): TestCase("Operator ->")
    {
        OpArrow();
        OpArrowConst();
    }
};


struct TestAssignment : public TestCase
{
    void AssignFromSameClass()
    {
        shared_ptr<Base> spb(new Base);
        shared_ptr<Base> spb2;
        spb2 = spb;
        CheckEqual(spb, spb2);
    }

    void AssignFromDerivedClass()
    {
        shared_ptr<Derived> spd(new Derived);
        shared_ptr<Base> spb2;
        spb2 = spd;
        CheckEqual(spd, spb2);
    }


    // THIS WILL NOT COMPILE
    //void AssignFromUnrelatedClass()
    //{
    //    shared_ptr<Derived> spd(new Derived);
    //    shared_ptr<int> spb2;
    //    spb2 = spd;
    //    CheckEqual(spd, spb2);
    //}



    TestAssignment(): TestCase("Assignment")
    {
        AssignFromSameClass();
        AssignFromDerivedClass();


    }
};






int main()
{
    TestOpArrow runTestOpArrow;
    TestAssignment runTestAssignment;
    TestConversionOps runTestConversoinOps;
    TestGetCPtr runTestCPtr;
    TestCtor runTestCtor;
    return 0;
}





//int main()
//{
//    shared_ptr<int> sp(new int(5));
//    cout << sp.CountRefs() << '\n';
//    
//    shared_ptr<int> sp2;
//
//    sp2 = sp;
//    cout << sp.CountRefs() << '\n';
//    cout << sp2.CountRefs() << '\n';
//
//    shared_ptr<int> sp3(sp2);
//     
//    cout << sp.CountRefs() << '\n';
//    cout << sp3.CountRefs() << '\n';
//
//    
//    shared_ptr<Derived> spd(new Derived());
//    shared_ptr<Base> spb(spd);
//    cout << spb.CountRefs() << '\n';
//
//    shared_ptr<Base> spb2;
//    spb2 = spd;
//
//    cout << spb.CountRefs() << '\n';
//
//    spd.Release();
//    cout << spb.CountRefs() << '\n';
//
//    spb.Release();
//    cout << spb2.CountRefs() << '\n';
////
//    spb2.Release();
//
//	return 0;
//}
