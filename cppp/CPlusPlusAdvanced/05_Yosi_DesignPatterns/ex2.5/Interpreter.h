/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-07    
    Last modified date:		2013-11-07
    Description: 	convert decimal number to roman numerals
****************************************************************************/

#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

enum Numbers
{
	ONE,
	FOUR,
	FIVE,
	NINE
}

class Dec2Roman_t
{
public:
	// CTOR, DTOR
	virtual ~Dec2Roman_t();
	explicit Dec2Roman_t();
	
	// empty CTOR to prevent infinite loop
	explicit Dec2Roman_t(int) {}
	
	std::string& interpret(int _num);
	
	virtual void interpretImp(int _num, std::string& _result) {};
	
	void Clean()	{ result.clear(); }
	
protected:
	
	virtual char	one() 	{ return 'I'; }
	virtual char*	four()  { return "IV"; }
	virtual char	five()	{ return 'I'; }
	virtual char*	nine()	{ return "XI"; }
	
	virtual int		factor() { return 1; }
	
private:
	std::string result;
	
	Dec2Roman_t* ones;
	Dec2Roman_t* tens;
	Dec2Roman_t* hundreds;
	Dec2Roman_t* thousands;
	
	// no copy
	Dec2Roman_t(const Dec2Roman_t& _d2r);
	Dec2Roman_t& operator =(const Dec2Roman_t& _d2r);
};
// ===================================================================== //


class Thousands_t : public Dec2Roman_t
{
public:
	Thousands_t() : Dec2Roman_t(1) {};
	virtual ~Thousands_t() {};
	
	virtual void interpretImp(int _num, std::string& _result);
	
protected:
	virtual char	one() 	{ return 'M'; }
	virtual char*	four()  { return "IV"; }
	virtual char	five()	{ return 'V'; }
	virtual char*	nine()	{ return "XI"; }
	
	virtual int		factor() { return 1000; }
};
// ===================================================================== //


//class Ones2Hundreds_t : public Dec2Roman_t
//{
//public:
//	Ones2Hundreds_t() : Dec2Roman_t(1) {};
//	virtual ~Ones2Hundreds_t() {};
//	
//	virtual void interpretImp(int _num, std::string& _result);
//	
//private:
//	static const char** Lookups[3];
//	
//	static const char* OnesLookup[4];
//	static const char* TensLookup[4];
//	static const char* HundredsLookup[4];
//};
// ===================================================================== //


class Hundreds_t : public Dec2Roman_t
{
public:
	Hundreds_t() : Dec2Roman_t(1) {};
	
protected:
	virtual char	one() 	{ return 'C'; }
	virtual char*	four()  { return "CD"; }
	virtual char	five()	{ return 'D'; }
	virtual char*	nine()	{ return "CM"; }
	
	virtual int		factor() { return 100; }
};
// --------------------------------------------------------------------- //

class Tens_t : public Dec2Roman_t
{
public:
	Tens_t() : Dec2Roman_t(1) {};
	
protected:
	virtual char	one() 	{ return 'X'; }
	virtual char*	four()  { return "XL"; }
	virtual char	five()	{ return 'L'; }
	virtual char*	nine()	{ return "XC"; }
	
	virtual int		factor() { return 10; }
};
// --------------------------------------------------------------------- //

class Ones_t : public Dec2Roman_t
{
public:
	Ones_t() : Dec2Roman_t(1) {};
	
protected:
	
	// inherited
//	virtual char	one() 	{ return 'I'; }
//	virtual char*	four()  { return "IV"; }
//	virtual char	five()	{ return 'V'; }
//	virtual char*	nine()	{ return "XI"; }
//	
//	virtual int		factor() { return 1; }
};

// ===================================================================== //


#endif  /* __INTERPRETER_H__ */
