#include <iostream>

#include "threadpool.h"
#include "runnable.h"
#include "semaphoremy.h"

using namespace std;



typedef double (*MathFunc)(double _x);

double PowerThree(double _x)
{
	return _x * _x * _x;
}


class IntegralCalculator
{
public:
	IntegralCalculator(MathFunc _func, double _from, double _to, unsigned int _accuracy)
	:m_sum(0), m_func(_func) ,m_from(_from), m_to(_to), m_accuracy(_accuracy) {}

	void Calculate()
	{ 
		double interval = (m_to - m_from) / m_accuracy;
			
		for (unsigned int i = 0; i < m_accuracy; ++i)
		{
			m_sum += (m_func( m_from)) * interval;
			m_from += interval;
		}
	}

	double GetSum() 
	{
		return m_sum;
	}

private:
	double m_sum;
	MathFunc m_func;
	double m_from;
	double m_to;
	
	unsigned int m_accuracy;
};



int main()
{
	Threadpool tp(2);

	IntegralCalculator cal1(PowerThree, 0.0, 5.0,  500000);
	IntegralCalculator cal2(PowerThree, 5.0, 10.0, 500000);

	RunShared run1 ( new MemberMethodRun<IntegralCalculator, &IntegralCalculator::Calculate>(cal1));
	RunShared run2 ( new MemberMethodRun<IntegralCalculator, &IntegralCalculator::Calculate>(cal2));


	tp.AddTask( run1, Threadpool::PRI_MED);
	tp.AddTask( run2, Threadpool::PRI_MED);

	tp.GracefullShutdown();	

	cout << (cal1.GetSum() + cal2.GetSum() ) << endl;


	Threadpool tp1(2);
	if (tp1.ImidiateShutdown( static_cast<float>(0.00000001) ) == true)
	{
		cout << "Fail, gracefully with short time" << endl;
	}

/*
	Threadpool tp5(2);
	if (tp5.ImidiateShutdown(1) == false)
	{
		cout << "Fail, ended not gracefully with long time" << endl;
	}
*/

    return 0;
}






