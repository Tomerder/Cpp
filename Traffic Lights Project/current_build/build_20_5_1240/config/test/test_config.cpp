#include <stdio.h>
#include <pthread.h>

#include "config.h"

char key[20][2] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"};

void* test1(void*)
{
	for(int i=0 ; i < 20 ; ++i )
	{
		printf("%s\n", ConfigGet(key[i],"fail"));
	}
	return 0;
}

void* test2(void*)
{
	for(int i=0 ; i < 20 ; ++i )
	{
		printf("%s\n", ConfigGet(key[i],"fail"));
	}
	return 0;
}

void* test3(void*)
{
	for(int i=0 ; i < 20 ; ++i )
	{
		printf("%s\n", ConfigGet(key[i],"fail"));
	}
	return 0;
}
	

int main()
{
	ConfigRead("config.txt");
	
	pthread_t t3,t1,t2;
	void* s1,*s2,*s3;
	
	pthread_create(&t1,0,test1,0);
	pthread_create(&t2,0,test2,0);
	pthread_create(&t3,0,test3,0);
	
	pthread_join(t1,&s1);
	pthread_join(t2,&s2);
	pthread_join(t3,&s3);
	
	printf("%s\n", ConfigGet("LOG_FLA","fail"));
	printf("%s\n", ConfigGet("LOG_FLAGS","fail"));
	printf("%s\n", ConfigGet("NULL","fail"));
	
	printf("%s\n", ConfigGet("#","success"));
	printf("%s\n", ConfigGet("asdsa","success"));
		
	return 0;
}
