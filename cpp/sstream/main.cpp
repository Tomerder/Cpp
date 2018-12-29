#include <iostream>
#include <sstream>
#include <string.h>
#include <iomanip>

using namespace std;

#define FLD1_W 10
#define FLD2_W 15
#define FLD3_W 20

/*------------------------------------------------------------------------------------*/

ostream& tableHdr(ostream& _os);
ostream& addToTable(ostream& _os, int _id , string _name ,string _adr);
ostream& tableLine(ostream&) ;

/*------------------------------------------------------------------------------------*/
int main() 
{
	ostringstream os;
	
	os << tableHdr << ends;
	
	cout << os.str() ;

	return 0;
}
/*------------------------------------------------------------------------------------*/
ostream& tableHdr(ostream& _os)
{
	return (_os << tableLine  << endl << setfill(' ') <<
								"|" << setw(FLD1_W) << left << "id" << "|" << 
							    "|" << setw(FLD2_W) << left << "name" << "|" << 
							    "|" << setw(FLD3_W) << left << "address" << "|" << 
							    endl << tableLine  );
}

/*------------------------------------------------------------------------------------*/
ostream& addToTable(ostream& _os, int _id , string _name ,string _adr)
{

	return (_os << endl << "|" << setw(FLD1_W) << right << _id << "|" << 
						  "|" << setw(FLD2_W) << left << _name << "|" <<
						  "|" << setw(FLD2_W) << left << _name << "|" << 
						  endl  << tableLine ) ;
} 

/*------------------------------------------------------------------------------------*/
ostream& tableLine(ostream& _os)  
{
	_os.
	return (_os << endl << setw(FLD1_W + FLD2_W + FLD3_W + 3 + 2) << setfill('-') << endl );

}


/*------------------------------------------------------------------------------------*/

