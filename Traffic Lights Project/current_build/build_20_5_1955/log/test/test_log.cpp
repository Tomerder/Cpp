#include <pthread.h>

#include "log.h"


void* test(void*)
{
	int i = 100;
	while(--i)
		ToLog(LOG_DEBUG, Message("tread1"));

    return 0;
}

void* test1(void*)
{
	int i = 100;
	while(--i)
		ToLog(LOG_DEBUG, Message("tread2"));

    return 0;
}

int main()
{
	LogCreate("testlog.txt" , LOG_DEBUG );
	
	pthread_t t,t1;
	void* s,*s1;
	
	pthread_create(&t,0,test,0);
	pthread_create(&t1,0,test1,0);
	
	int i = 10;
	while(--i)	
	 	ToLog(LOG_DEBUG, Message("main"));
	
	pthread_join(t,&s);	
	pthread_join(t1,&s1);
	
	return 0;
}
