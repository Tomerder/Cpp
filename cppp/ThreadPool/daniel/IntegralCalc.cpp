#include <iostream>
#include <unistd.h>
#include "threadpool.h"
#include "runnable.h"

#define F(x) ((x)*(x)*(x))

using namespace std;
using namespace m10;


class CalcInterval: public Runnable
{
public:
    CalcInterval(double start, double end, double& result):
                m_start(start), m_end(end), m_result(result)
    {
    }

    virtual void operator()()
    {
        int div = 1000000000;
        double res = 0;
        double interval = (m_end - m_start)/div;
        double beginFrom = m_start + interval/2;

        for (int i=0; i<div; ++i)
        {
            res += interval * F(beginFrom +  i*interval);
        }

        m_lock.Lock();
        m_result += res;
        m_lock.Unlock();
        cout << "Thread " << Thread::GetID() << " calculated " << res << endl;
    }

private:
    double m_start;
    double m_end;
    double& m_result;
    Mutex m_lock;
};


int main()
{
    double result = 0;
    shPtrRunbl_t interval1(new CalcInterval(0, 1, result));
    shPtrRunbl_t interval2(new CalcInterval(1, 2, result));
    shPtrRunbl_t interval3(new CalcInterval(2, 3, result));
    shPtrRunbl_t interval4(new CalcInterval(3, 4, result));
    ThreadPool pool(2);

    pool.AddTask(interval1, PRI_HIGH);
    pool.AddTask(interval2, PRI_LOW);
    pool.AddTask(interval3, PRI_LOW);
    pool.AddTask(interval4, PRI_MED);

    pool.GracefullShutDown();
    //pool.ImmidiateShutDown(6);
    cout << "Integral result is " << result << endl;


    return 0;
}
