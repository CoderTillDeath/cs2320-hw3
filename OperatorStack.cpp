#include <iostream>
using namespace std;

struct Operator
{
	char op;
	Operator * next;
};

Operator * newOp(char op)
{
	Operator * v = new Operator;
	v->op = op;
	v->next = NULL;
	return v;
}

struct OperatorStack {
	Operator * top;
};

OperatorStack * newOperatorStack()
{
	OperatorStack * s = new OperatorStack;
	s->top = NULL;
	return s;
}

Operator * pop(OperatorStack * s)
{
	Operator * v = s->top;
	s->top = v->next;
	return v;
}

Operator * queryTop(OperatorStack * s)
{
	return s->top;
}

void push(Operator * v, OperatorStack * s)
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

bool isEmpty(OperatorStack * s)
{
	return s->top == NULL;
}

char getValue(Operator * op)
{
	return op->op;
}
