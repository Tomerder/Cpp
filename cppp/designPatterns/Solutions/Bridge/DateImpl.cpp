#include <iostream>
#include <iomanip>
#include <string>


using namespace std;
class DateImpl;

class Date {
public:
   Date(int day, int month , const string& Impl) {
	   if (Impl=="Hebrew")
 			m_Date = new HebrewDateImpl( day, month );
	   else if (Impl=="Arabic")
 			m_Date = new ArabicDateImpl( day, month );
	   else m_Date = 0;
  }
   virtual void tell() { m_Date->tell(); }
protected:
   DateImpl*  m_Date;
};


class DateImpl {
public:
	DateImpl( int day, int month ) { d = day;  m = month; }
	virtual void tell() { 
	   cout << "Date is :" << d <<"/" << m << endl; 
	}
protected:
   int d, m;
};

class HebrewDateImpl : public DateImpl {
public:
	HebrewDateImpl( int day, int month) 
		: DateImpl( day, month ) {/*..*/ }
};

class ArabicDateImpl : public DateImpl {
public:
	ArabicDateImpl( int day, int month) 
		: DateImpl( day, month ) {/*..*/ }
};



Date* createDate(int day, int month, const string& Impl) {
	return new Date( 14, 05 ,Impl);
}

void main() {
   Date*  Dates[2];
   Dates[0] = createDate( 2, 12, "Hebrew");
   Dates[1] = createDate( 14, 11, "Arabic");
   for (int i=0; i < 2; i++)
      Dates[i]->tell();
}

