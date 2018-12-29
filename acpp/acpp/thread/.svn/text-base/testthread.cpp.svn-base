#include <iostream>
#include <unistd.h>

#include "mutex.h"
#include "semaphoremy.h"
#include "priorityqueue.h"
#include "thread.h"
#include "runnable.h"


using namespace std;
using namespace std::tr1;


typedef enum {OK, ERROR} TEST;
TEST GlobalTest();
TEST DetachedTest();
TEST MemberFuncTest();
TEST MemberFuncDetachedTest();
TEST TimeOutThreadTest();

int main()
{
 	const string pass = "Pass", fail = "fail";

 	//Unit test.
	//case 1:
	cout << "\nGlobal function Test:" << ((GlobalTest()==OK) ? pass : fail) << endl;

	//case 2:
	cout << "\nDetached thread Test:" << ((DetachedTest()==OK) ? pass : fail) << endl;

	//case 3:
	cout << "\nMember function Test:" << ((MemberFuncTest()==OK) ? pass : fail) << endl;

	//case 5:
	cout << "\nJoin with timer Test:" << ((TimeOutThreadTest()==OK) ? pass : fail) << endl;


	//case 4:
	cout << "\nMember Func detached Test:" << ((MemberFuncDetachedTest()==OK) ? pass : fail) << endl;


    return 0;
}

//-----------------------------------------------------
//      Global functions
int g_int = 0;

void Foo()
{
    ++g_int;
}

TEST GlobalTest()
{
    if (g_int != 0) return ERROR;

    shared_ptr<Runnable> a(new FunctionRun<Foo> );
    Thread t( a, true);

    t.Join();

    if (g_int != 1) return ERROR;
    return OK;
}


TEST DetachedTest()
{
    shared_ptr<Runnable> a(new FunctionRun<Foo> );

    Thread t( a, false);

    usleep(100);
    if (g_int != 2) return ERROR;
    return OK;
}
//-----------------------------------------------------
//      Member functions
class X{
public:
    X():m_count(0){};

    void Bar()
    {
        ++m_count;
    }

    int m_count;
};

TEST MemberFuncTest()
{
    X x;

    shared_ptr<Runnable> a(new MemberMethodRun<X,&X::Bar>(x));

    Thread t( a, true);

    t.Join();

    if (x.m_count != 1) return ERROR;
    return OK;
}

TEST MemberFuncDetachedTest()
{
    X x;

    shared_ptr<Runnable> a(new MemberMethodRun<X,&X::Bar>(x) );
    Thread t( a, false);

    usleep(100);
    if (x.m_count != 1) return ERROR;
    return OK;
}

int g_stop = 1;
void Kuku()
{
    while (g_stop){
    usleep(10000);
    ++g_int;
   // cout << g_int;
    }

}

TEST TimeOutThreadTest()
{
    shared_ptr<Runnable> a(new FunctionRun<Kuku>);

    Thread t(a, true);

    if (t.JoinTimeout(0.7) != true )
    {
        t.Cancel();
    }

    return OK;
}

