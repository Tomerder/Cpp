#include <iostream>
#include <string.h>

#include "tmpl.h"

using namespace std;

/*------------------------------------------------------------------------------------*/

void Test();

/*------------------------------------------------------------------------------------*/


int main() 
{
	Test();

	return 0;
}


/*------------------------------------------------------------------------------------*/

void Test()
{
	Tmpl<string> tmpl;
	Tmpl<string> tmpl2("zzz");
	Tmpl<string> tmpl3;
	
	cout << "/--------------------------------------------------------------/" << endl;
	cout << "Tmpl<string> tmpl2('zzz');" << endl;
	cout << "tmpl data: " <<  tmpl.GetData()  << "  , tmpl ref count: " << tmpl.GetRefCount() << endl ;
	cout << "tmpl2 data: " <<  tmpl2.GetData()  << "  , tmpl2 ref count: " << tmpl2.GetRefCount() << endl ;
	cout << "tmpl3 data: " <<  tmpl3.GetData()  << "  , tmpl3 ref count: " << tmpl3.GetRefCount() << endl ;
	cout << "/--------------------------------------------------------------/" << endl;
	
	tmpl.SetData("ttt");	
	cout << "tmpl.SetData('ttt');" << endl;
	cout << "tmpl data: " <<  tmpl.GetData()  << "  , tmpl ref count: " << tmpl.GetRefCount() << endl ;
	cout << "/--------------------------------------------------------------/" << endl;
	
	tmpl3 = tmpl2;
	cout << "tmpl3 = tmpl2;" << endl;
	cout << "tmpl data: " <<  tmpl.GetData()  << "  , tmpl ref count: " << tmpl.GetRefCount() << endl ;
	cout << "tmpl2 data: " <<  tmpl2.GetData()  << "  , tmpl2 ref count: " << tmpl2.GetRefCount() << endl ;
	cout << "tmpl3 data: " <<  tmpl3.GetData()  << "  , tmpl3 ref count: " << tmpl3.GetRefCount() << endl ;
	cout << "/--------------------------------------------------------------/" << endl;
	
	Tmpl<string> tmpl4(tmpl2);
	cout << "Tmpl<string> tmpl4(tmpl2);" << endl;
	cout << "tmpl data: " <<  tmpl.GetData()  << "  , tmpl ref count: " << tmpl.GetRefCount() << endl ;
	cout << "tmpl2 data: " <<  tmpl2.GetData()  << "  , tmpl2 ref count: " << tmpl2.GetRefCount() << endl ;
	cout << "tmpl3 data: " <<  tmpl3.GetData()  << "  , tmpl3 ref count: " << tmpl3.GetRefCount() << endl ;
	cout << "tmpl4 data: " <<  tmpl4.GetData()  << "  , tmpl4 ref count: " << tmpl4.GetRefCount() << endl ;
	cout << "/--------------------------------------------------------------/" << endl;
	
	tmpl = tmpl4;
	cout << "tmpl = tmpl4;" << endl;
	cout << "tmpl data: " <<  tmpl.GetData()  << "  , tmpl ref count: " << tmpl.GetRefCount() << endl ;
	cout << "tmpl2 data: " <<  tmpl2.GetData()  << "  , tmpl2 ref count: " << tmpl2.GetRefCount() << endl ;
	cout << "tmpl3 data: " <<  tmpl3.GetData()  << "  , tmpl3 ref count: " << tmpl3.GetRefCount() << endl ;
	cout << "tmpl4 data: " <<  tmpl4.GetData()  << "  , tmpl4 ref count: " << tmpl4.GetRefCount() << endl ;
	cout << "/--------------------------------------------------------------/" << endl;
	
	tmpl.SetData("yyy");
	cout << "tmpl.SetData('yyy');" << endl;
	cout << "tmpl data: " <<  tmpl.GetData()  << "  , tmpl ref count: " << tmpl.GetRefCount() << endl ;
	cout << "tmpl2 data: " <<  tmpl2.GetData()  << "  , tmpl2 ref count: " << tmpl2.GetRefCount() << endl ;
	cout << "tmpl3 data: " <<  tmpl3.GetData()  << "  , tmpl3 ref count: " << tmpl3.GetRefCount() << endl ;
	cout << "tmpl4 data: " <<  tmpl4.GetData()  << "  , tmpl4 ref count: " << tmpl4.GetRefCount() << endl ;
	cout << "/--------------------------------------------------------------/" << endl;
	
	tmpl2.SetData(tmpl.GetData());
	cout << "tmpl2.SetData(tmpl.GetData());" << endl;
	cout << "tmpl data: " <<  tmpl.GetData()  << "  , tmpl ref count: " << tmpl.GetRefCount() << endl ;
	cout << "tmpl2 data: " <<  tmpl2.GetData()  << "  , tmpl2 ref count: " << tmpl2.GetRefCount() << endl ;
	cout << "tmpl3 data: " <<  tmpl3.GetData()  << "  , tmpl3 ref count: " << tmpl3.GetRefCount() << endl ;
	cout << "tmpl4 data: " <<  tmpl4.GetData()  << "  , tmpl4 ref count: " << tmpl4.GetRefCount() << endl ;
	cout << "/--------------------------------------------------------------/" << endl;

	tmpl3 = tmpl2;
	cout << "tmpl3 = tmpl2;" << endl;
	cout << "tmpl data: " <<  tmpl.GetData()  << "  , tmpl ref count: " << tmpl.GetRefCount() << endl ;
	cout << "tmpl2 data: " <<  tmpl2.GetData()  << "  , tmpl2 ref count: " << tmpl2.GetRefCount() << endl ;
	cout << "tmpl3 data: " <<  tmpl3.GetData()  << "  , tmpl3 ref count: " << tmpl3.GetRefCount() << endl ;
	cout << "tmpl4 data: " <<  tmpl4.GetData()  << "  , tmpl4 ref count: " << tmpl4.GetRefCount() << endl ;
	cout << "/--------------------------------------------------------------/" << endl;	
	
}

/*------------------------------------------------------------------------------------*/



