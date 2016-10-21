#include <iostream>
#include <fstream>
using namespace std;

enum type_statement {
	open,
	close,
	buy,
	add,
	times,
	discount,
	total,
	price
};

string before(string s, string b)
{
    return s.substr(0,s.find(b));
}

string after(string s, string b)
{
    return s.substr(s.find(b)+1);
}

struct lineSplit {
	string name;
	string op;
	string value;
};

lineSplit * newLineSplit()
{
	lineSplit * split = new lineSplit;
	split->name = "";
	split->op = "";
	split->value = "";
	return split;
}

struct Operator
{
	char op;
	OperatorOrPrice * next;
};

Operator * newOp(char op)
{
	OperatorOrPrice * v = new OperatorOrPrice;
	v->op = op;
	v->next = NULL;
	return v;
}

struct OperatorStack {
	Operator * top;
};

OperatorStack * newStack()
{
	OperatorStack * s = new OperatorStack;
	s->top = NULL;
	return s;
}

Operator * pop(stack * s)
{
	Operator * v = s->top;
	s->top = v->next;
	return v;
}

struct Person 
{
    OperatorStacki * ops;
    ValueStack * vals; 
}

struct People
{
    Person * first;
    Person * last;
}

void push(OperatorOrPrice * v, stack * s)
{
	if(s->top == NULL)
	{
		s->top = v;
	}
	else
	{
		v->next = s->top;
		s->top = v;
	}
}

bool isEmpty(stack * s)
{
	return s->top == NULL;
}

bool isNumber(char c)
{
	return (int)c > 47 && (int)c < 58;
}

lineSplit * split(string line)
{
	lineSplit * split = newLineSplit();
	
	split->name = before(line, "\t");
	split->op = before(after(line, "\t"), "\t");
	split->value = after(after(line, "\t"), "\t");
	
	return split;
}

bool equals(string s1, string s2)
{
	return s1.compare(s2) == 0;
}

type_statement getTypeStatement(lineSplit * sp)
{
	string s = sp->op;
	string name = sp->name;
	if(equals(s,"open")) 		return open;
	if(equals(s,"close")) 		return close;
	if(equals(s,"buy")) 		return buy;
	if(equals(s,"add")) 		return add;
	if(equals(s,"times")) 		return times;
	if(equals(s,"discount%")) 	return discount;
	if(equals(s,"total")) 		return total;
	if(equals(name,"price")) 	return price;
}


int main(int argc, char ** argv)
{
    string filename = argv[1];
    filename = filename.substr(6);
    ifstream file(filename);
    
    Prices * prices = newPrices();
    People * people = newPeople();
    
    string line = "";
    
    while (getline(file,line))
    {
        if(line.length() != 0 && line.at(0) != '#')
        {
            lineSplit * s = split(line);
            
            switch(getTypeStatement(s))
            {
				case price: addPrice(p, s->op, s->value);
							break;
				case buy:	pushValue(people, s->name, s->value);
							break;
				case open:	handleOperator(people, s->name, '(');
							break;
				case close:	handleOperator(people, s->name, ')');
							break;
				case add:	handleOperator(people, s->name, '+');
                            pushValue(people, s->name, s->value);
							break;
				case times:	handleOperator(people, s->name, '*');
                            pushValue(people, s->name, s->value);
							break;
				case discount:
                            handleDiscount(people, s->name, s->value);
							break;
				case total:	getTotal(people,s->name);
							break;
				
			}
        }
    }
}
 
