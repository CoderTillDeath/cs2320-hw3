#include <iostream>
using namespace std;

bool equals(string,string);

struct Price 
{
	string item;
	double value;
	Price * next;
};

Price * newPrice(string item, string price)
{
	Price * p = new Price;
	p->item = item;
	p->value = stoi(price);
	return p;
}

struct Prices
{
	Price * top;
};

Prices * newPrices()
{
	Prices * p = new Prices;
	p->top = NULL;
	return p;
}

Price * contains(Prices * ps, string name)
{
	for(Price * current = ps->top; current; current = current->next)
	{
		if(equals(current->item, name))
		{
			return current;
		}
	}
	
	return NULL;
}

void insert(Prices* ps, Price * p)
{
	Price * current = contains(ps, p->item);
	
	if(current == NULL)
	{
		if(ps->top == NULL)
		{
			ps->top = p;
		}
		else
		{
			p->next = ps->top;
			ps->top = p;
		}
	}
	else
	{
		current->value = p->value;
	}
}

void addPrice(Prices* p, string item, string price)
{
	insert(p, newPrice(item,price));
}

double getPrice(Prices* p,string name)
{
	return contains(p, name)->value;
}
