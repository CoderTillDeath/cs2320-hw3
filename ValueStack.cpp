#include <iostream>
using namespace std;

struct Value {
	double value;
	Value * next;
};

Value * newValue(double d) {
	Value * v = new Value;
	v->value = d;
	v->next = NULL;
	return v;
}

struct ValueStack
{
	Value * top;
};

ValueStack * newValueStack() {
	ValueStack * s = new ValueStack;
	s->top = NULL;
	return s;
}

Value * pop(ValueStack * s)
{
	Value * v = s->top;
	s->top = v->next;
	return v;
}

Value * queryTop(ValueStack * s)
{
	return s->top;
}

void push(Value * v, ValueStack * s)
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

double getValue(Value * v)
{
	return v->value;
}

void apply(ValueStack* s,char c)
{
	double arg2 = pop(s)->value;
	double arg1 = pop(s)->value;
	
	double result;
	
	switch((int)c)
	{
		case (int)'+':	result = arg1 + arg2;
						break;
		case (int)'-':	result = arg1 - arg2;
						break;
		case (int)'*':	result = arg1 * arg2;
						break;
		case (int)'/':	result = arg1 / arg2;
						break;
	}
	
	push(newValue(result),s);
}
