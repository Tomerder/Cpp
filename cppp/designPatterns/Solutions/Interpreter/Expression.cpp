#include <iostream>
#include <string>
#include <map>
using namespace std;
 


class Expression {
public:
	virtual int Interpret(map<string, int> variables) {}
}
 
class Number : Expression
{
public 
	int number;
	Number(int number) { this.number = number; }
	int Interpret(map<string, int> variables) { return number; }
}

abstract class BasicOperation : Expression
{
    Expression leftOperator, rightOperator;

    public BasicOperation(IExpression left, IExpression right)
    {
        leftOperator = left;
        rightOperator = right;
    }

    public int Interpret(Dictionary<string, int> variables)
    {
        return Execute(leftOperator.Interpret(variables), rightOperator.Interpret(variables));
    }

    abstract protected int Execute(int left, int right);
}

class Plus : BasicOperation
{
    public Plus(IExpression left, IExpression right) : base(left, right) { }

    protected override int Execute(int left, int right)
    {
        return left + right;
    }
}

class Minus : BasicOperation
{
    public Minus(IExpression left, IExpression right) : base(left, right) { }

    protected override int Execute(int left, int right)
    {
        return left - right;
    }
}

class Variable : Expression
{
    private string name;

    public Variable(string name) { this.name = name; }

    public int Interpret(Dictionary<string, int> variables)
    {
        return variables[name];
    }
}

class Evaluator
{
    private Expression syntaxTree;

    public Evaluator(string expression)
    {
        Stack<Expression> stack = new Stack<Expression>();
        foreach (string token in expression.Split(' '))
        {
            if (token.Equals("+"))
                stack.Push(new Plus(stack.Pop(), stack.Pop()));
            else if (token.Equals("-")){
				Expression right = stack.Pop();
				Expression left = stack.Pop();
                stack.Push(new Minus(left, right));
            }else
                stack.Push(new Variable(token));
        }
        syntaxTree = stack.Pop();
    }

    public int Evaluate(map<string, int> context)
    {
        return syntaxTree.Interpret(context);
    }
}
 

int	main() {
    Evaluator evaluator = new Evaluator("w x z - +");
    map<string, int> values = new Dictionary<string,int>();
    values.Add("w", 5);
    values.Add("x", 10);
    values.Add("z", 42);
    Console.WriteLine(evaluator.Evaluate(values));
}
