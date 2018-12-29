// This class library is an example of the Interpreter Design Pattern
// This particular example is an Interpreter from Roman Numerals to decimal
// The classes Thousand, Hundred, Ten and One are examples of
// TerminalExpression classes

#include <iostream>
#include <string>
using namespace std;


class Thousand;
class Hundred;
class Ten;
class One;

class Interpreter {
public:

	Interpreter();

	Interpreter( int ) {}

	// This is the overloaded method Interpret which invokes
	// the Interpret method from the class Interpreter

	int interpret( char* input ) {
		int total = 0;
		thousands->interpret( input, total );
		hundreds->interpret( input, total );
		tens->interpret( input, total );
		ones->interpret( input, total );
		if (strcmp(input, ""))  return 0;
		return total;
	}


// The method Interpret checks the context against the TerminalExpression
// classes and computes the interpreted results.
// It then removes the interpreted result from the context so that the 
// next iteration will only have the uninterpreted part.
   virtual void interpret( char* input, int& total ) {
	   int index = 0;

	   if ( ! strncmp(input, nine(), 2)) {
		   total += 9 * multiplier();
		   index += 2;

	   } else if ( ! strncmp(input, four(), 2)) {
		   total += 4 * multiplier();
		   index += 2;
       } else {
			if (input[0] == five()) {
			   total += 5 * multiplier();
			   index = 1;
			}  else {
				index = 0;
			}

           for (int end = index + 3 ; index < end; index++)
               if (input[index] == one())
					total += 1 * multiplier();
               else
                   break;
       }
       strcpy( input, &(input[index]));
    }

protected:
    virtual char	one()       { return '1';}
    virtual char*	four()		{ return "4";}
    virtual char	five()      { return '5'; }
    virtual char*	nine()		{ return "9";}
    virtual int		multiplier(){ return  1;}

private:
    Interpreter* thousands;
    Interpreter* hundreds;
    Interpreter* tens;
    Interpreter* ones;
};



// The class Thousand checks for occurances of the Roman Numeral M

class Thousand : public Interpreter {
public:
	Thousand( int ) : Interpreter(1) { }
protected:
    char	one()		{ return 'M'; }
    char*	four()		{ return ""; }
    char	five()      { return '\0'; }
    char*	nine()		{ return ""; }
    int		multiplier(){ return 1000; }
};



// The class Hundred checks for occurances of the Roman Numerals
// C, CD, D or CM

class Hundred : public Interpreter {
public:
    Hundred( int ) : Interpreter(1) { }
protected:
    char	one()		{ return 'C';}
    char*	four()		{ return "CD";}
    char	five()		{ return 'D';}
    char*	nine()		{ return "CM";}
    int		multiplier(){ return 100;}
};

// The class Ten checks for occurances of the Roman Numerals 
// X, XL, L and XC

class Ten : public Interpreter {
public:
    Ten( int ) : Interpreter(1) { }
protected:
    char	one()      { return 'X'; }
    char*	four()		{ return "XL"; }
    char	five()      { return 'L'; }
    char*	nine()		{ return "XC"; }
    int		multiplier(){ return 10; }
};



// The class One checks for occurances of the Roman Numerals from 1 to 9

class One : public Interpreter {
public:
    One( int ) : Interpreter(1) { }
protected:
    char	one()		{ return 'I';}
    char*	four()		{ return "IV";}
    char	five()      { return 'V'; }
    char*	nine()		{ return "IX";}
    int		multiplier(){ return 1; }

};

Interpreter::Interpreter() {
	thousands = new Thousand(4);
	hundreds  = new Hundred(4);
	tens      = new Ten(4);
	ones      = new One(4);
}

//-------------------------------------------------------

int main() {
	Interpreter RomDec;

	int result;
	char* cp = new char[10];
	strcpy(cp,"MMCDXLIX");
	result = RomDec.interpret(cp);
	cout << result << endl;

	delete[] cp;
	return 0;
}


