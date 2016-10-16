#include <iostream>
using namespace std;

struct symb {
	char op;
	int num;
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

symb * newSymb(int a)
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



int eval(stack * s)
{
	symb * sym = pop(s);
	if(sym->isNumber)
	{
		return sym->num;
	}
	else
	{
		switch((int)sym->op)
		{
			case 43: return eval(s) + eval(s);
			 		 break;
			case 45: return eval(s) - eval(s);
					 break;
			case 42: return eval(s) * eval(s);
					 break;
			case 47: return eval(s) / eval(s);
					 break;
		}
	}
}

int main()
{
	stack * s = newStack();
	
	push(newSymb(1),s);
	push(newSymb(2),s);
	push(newSymb(3),s);
	push(newSymb('+'),s);
	push(newSymb('*'),s);
	
	cout << eval(s) << endl;
}
