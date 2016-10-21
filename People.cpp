#include <iostream>
using namespace std;

// OperatorStack
struct OperatorStack;
OperatorStack * newOperatorStack();
struct Operator;
Operator * newOp(char);
Operator * pop(OperatorStack *);
Operator * queryTop(OperatorStack*);
void push(Operator *, OperatorStack *);
char getValue(Operator*);
bool isEmpty(OperatorStack*);

// ValueStack
struct ValueStack;
ValueStack * newValueStack();
struct Value;
Value * newValue(double);
Value * pop(ValueStack*);
Value * queryTop(ValueStack*);
void push(Value *, ValueStack *);
double getValue(Value*);
void apply(ValueStack*, char op);

// Prices
struct Prices;
double getPrice(Prices*,string);

// Utilities
bool equals(string, string);
bool isNumber(string);
int getPriority(char c);

struct Person 
{
	string name;
    OperatorStack * ops;
    ValueStack * vals; 
    Person * next;
};

Person * newPerson(string name)
{
	Person * p = new Person;
	p->name = name;
	p->ops = newOperatorStack();
	p->vals = newValueStack();
    p->next = NULL;
	return p;
}

struct People
{
    Person * first;
    Person * last;
};

People * newPeople()
{
	People * p = new People;
	p->first = NULL;
	p->last = NULL;
	return p;
}

void add(People * ppl, Person * p)
{
	if(ppl->first == NULL)
	{
		ppl->first = p;
		ppl->last = p;
	}
	else
	{
		ppl->last->next = p;
		ppl->last = p;
	}
}

Person * getPerson(People * p, string name)
{
	for(Person * current = p->first; current; current = current->next)
	{
		if(equals(current->name, name))
		{
			return current;
		}
	}
	
	Person * n = newPerson(name);
	
	add(p,n);
	
	return n;
}

void pushValue(People* people, Prices * prices,string name, string value)
{
	Person * p = getPerson(people, name);
	
	if(isNumber(value))
	{
		int a = stoi(value);
	
		push(newValue(a),p->vals);
	}
	else
	{
		push(newValue(getPrice(prices,value)), p->vals);
	}
}

void handleOperator(People* people, string name, char op)
{
	Person * p = getPerson(people, name);
	
	OperatorStack * opstack = p->ops;
	ValueStack * valstack = p->vals;
	
	if(op == '(')
	{
		push(newOp(op),opstack);
		return;
	}
	
	while(queryTop(opstack) != NULL && getPriority(getValue(queryTop(opstack))) > getPriority(op))
	{
		apply(valstack, getValue(pop(opstack)));
	}
	
	push(newOp(op),opstack);
}

void handleDiscount(People* people, string name, string value)
{
	Person * p = getPerson(people, name);
	
	int a = stoi(value);
	double discount = ((double)100 - a)/100;
	
	handleOperator(people, name, '*');
	push(newValue(discount),p->vals);
}

void handleClose(People* people, string name)
{
	Person * p = getPerson(people, name);
	
	OperatorStack * opstack = p->ops;
	ValueStack * valstack = p->vals;
	
	while(getValue(queryTop(opstack)) != '(')
	{
		apply(valstack, getValue(pop(opstack)));
	}
	
	pop(opstack);
}

int getTotal(People* people,string name)
{
	Person * p = getPerson(people, name);
	OperatorStack * opstack = p->ops;
	
	while(!isEmpty(opstack))
	{
		apply(p->vals, getValue(pop(opstack)));
	}
	
	return (int)getValue(queryTop(p->vals));
}

