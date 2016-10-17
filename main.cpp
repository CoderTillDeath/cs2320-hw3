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
	total
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

struct symb {
	char op;
	double num;
	bool isNumber;
	symb * next;
};

symb * newSymb(char c)
{
	symb * v = new symb;
	v->next = NULL;
	v->num = 0;
	v->op = c;
	v->isNumber = false;
	return v;
}

symb * newSymb(double a)
{
	symb * v = new symb;
	v->next = NULL;
	v->num = a;
	v->op = -1;
	v->isNumber = true;
	return v;
}

struct stack {
	symb * top;
};

stack * newStack()
{
	stack * s = new stack;
	s->top = NULL;
	return s;
}

symb * pop(stack * s)
{
	symb * v = s->top;
	s->top = v->next;
	return v;
}

void push(symb * v, stack * s)
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

lineSplit * split(string line)
{
	lineSplit * split = newLineSplit();
	
	split->name = before(line, " ");
	split->op = before(after(line, " "), " ");
	split->value = after(after(line, " "), " ");
	
	return split;
}

bool equals(string s1, string s2)
{
	return s1.compare(s2) == 0;
}

type_statement getTypeStatement(string s)
{
	if(equals(s,"open")) 		return open;
	if(equals(s,"close")) 		return close;
	if(equals(s,"buy")) 		return buy;
	if(equals(s,"add")) 		return add;
	if(equals(s,"times")) 		return times;
	if(equals(s,"discount%")) 	return discount;
	if(equals(s,"total")) 		return total;
}

string convertToInfix(string filename)
{
    ifstream file(filename);
    
    string all = "";
    string line = "";
    
    while (getline(file,line))
    {
        if(line.length() != 0 && line.at(0) != '#')
        {
            lineSplit * s = split(line);
            
            switch(getTypeStatement(s->op))
            {
				case open:	
							break;
				case close:	
							break;
				case buy:	
							break;
				case add:	
							break;
				case times:	
							break;
				case discount:	
							break;
				case total:	
							break;
			}
        }
    }
    
    return all;
}

int main(int argc, char ** argv)
{
    string filename = argv[1];
    filename = filename.substr(6);
    
    ifstream file(filename);
    string line = "";
    
    getline(file,line);
    lineSplit * s = split(line);
    
    cout << s->name << "\t" << s->op << "\t" << s->value << endl;
    
    /*
    string infix = convertToInfix(filename);

    stack * output = newStack();
    stack * operators = newStack();*/
}
 
