/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-18
    Last modified date: 2013-11-18 
    Description : Uncopyable
***************************************************************************************/
#ifndef __UNCOPIABLE_H__
#define __UNCOPIABLE_H__

class Uncopyable
{
	public:
		Uncopyable (){};
		virtual ~Uncopyable (){};

	private:
		Uncopyable(const Uncopyable&);
		Uncopyable& operator=(const Uncopyable&);
};

#endif
