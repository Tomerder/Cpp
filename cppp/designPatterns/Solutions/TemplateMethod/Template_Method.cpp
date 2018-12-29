#include <stdlib.h>		// for rand function
#include <time.h>		// for time function
#include <iostream>

using namespace std;

class AbstractSort {  
public:
   void sort( int v[], int n ) {
      for (int g = n/2; g > 0; g /= 2)
         for (int i = g; i < n; i++)
            for (int j = i-g; j >= 0; j -= g)
               if (needSwap( v[j], v[j+g] ))
                  doSwap(v[j], v[j+g]);
   }
private:
   virtual int needSwap(int,int) = 0;
   void doSwap(int& a,int& b) {
      int t = a; a = b; b = t;
   }
};

class SortUp : public AbstractSort {
	virtual   int needSwap(int a, int b) { return (a > b);}
};

class SortDown : public AbstractSort {
	int needSwap(int a, int b) { return (a < b);}
};

int main( void ) {
   const int NUM = 10;
   int       array[NUM];
   srand( (unsigned) time(0) );
   
   for (int i=0; i < NUM; i++) {
      array[i] = rand() % 10 + 1;
      cout << array[i] << ' ';
   }
   cout << endl;

   AbstractSort* sortObjects[2];
   sortObjects[0] = new SortUp;
   sortObjects[1] = new SortDown;
   sortObjects[0]->sort( array, NUM );
   
   for (int u=0; u < NUM; u++)
      cout << array[u] << ' ';
   cout << endl;

   sortObjects[1]->sort( array, NUM );
   for (int d=0; d < NUM; d++)
      cout << array[d] << ' ';
   cout << endl;

   return 0;
}

