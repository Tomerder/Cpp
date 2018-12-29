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

	string interpret( string input ) {
		string roman = "";
        switch(input.length())
        {
            case 4:
                thousands->interpret( input, roman );
            case 3:
                hundreds->interpret( input, roman );
            case 2:
                tens->interpret( input, roman );
            case 1:
                ones->interpret( input, roman );
                break;
            default:
                return "";
        }
		return roman;
	}


// The method Interpret checks the context against the TerminalExpression
// classes and computes the interpreted results.
// It then removes the interpreted result from the context so that the 
// next iteration will only have the uninterpreted part.
   virtual void interpret( string& input, string& roman ) {

       switch(input[0])
       {
            case '9':
               roman += nine();
               break;
            case '4':
               roman += four();
               break;
            case '5':
               roman += five();
               break;
            case '0':
               break;
            default:
               if ( (input[0]-'0') > 5)
               {
                    roman += five();
                    input[0] = input[0] - 5; 
               } 
               while(input[0] != '0')
               {
                 roman += one();
                 input[0]--;
               }

               break;
       }


       input.erase(input.begin());
    }

protected:
    virtual string	one()       { return "1";}
    virtual string	four()		{ return "4";}
    virtual string	five()      { return "5"; }
    virtual string	nine()		{ return "9";}

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
    string	one()		{ return "M"; }
    string	four()		{ return ""; }
    string	five()      { return "\0"; }
    string	nine()		{ return ""; }
};



// The class Hundred checks for occurances of the Roman Numerals
// C, CD, D or CM

class Hundred : public Interpreter {
public:
    Hundred( int ) : Interpreter(1) { }
protected:
    string	one()		{ return "C";}
    string	four()		{ return "CD";}
    string	five()		{ return "D";}
    string	nine()		{ return "CM";}
};

// The class Ten checks for occurances of the Roman Numerals 
// X, XL, L and XC

class Ten : public Interpreter {
public:
    Ten( int ) : Interpreter(1) { }
protected:
    string	one()      { return "X"; }
    string	four()		{ return "XL"; }
    string	five()      { return "L"; }
    string	nine()		{ return "XC"; }
};



// The class One checks for occurances of the Roman Numerals from 1 to 9

class One : public Interpreter {
public:
    One( int ) : Interpreter(1) { }
protected:
    string	one()		{ return "I";}
    string	four()		{ return "IV";}
    string	five()      { return "V"; }
    string	nine()		{ return "IX";}

};

Interpreter::Interpreter() {
	thousands = new Thousand(4);
	hundreds  = new Hundred(4);
	tens      = new Ten(4);
	ones      = new One(4);
}

//-------------------------------------------------------

int main(int argc, char** argv) {

    Interpreter RomDec;

	string result;
	string cp(argv[1]);
	result = RomDec.interpret(cp);
	cout << result << endl;

	return 0;
}


