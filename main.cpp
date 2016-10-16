#include <iostream>
#include <fstream>
using namespace std;

struct value
{
    string operator;
    value * next;
};

value * newValue()
{
    value * v = new value;
    v->operator = "";
    v->next = NULL;
    return v;
}

struct stack
{
    value * top;
};

stack * newStack()
{
    stack * s = new stack;
    s->top = NULL;
    return s;
}

value * pop(stack * s)
{
    value * v = s->top;
    s->top = s->top->next;
    return v;
}

void push(stack * s, value * v)
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

void operate

int main(int argc, char ** argv)
{
    string filename = argv[1];
    filename = filename.substr(6);
    ifstream file(filename);

    stack * values = newStack();
    string line = "";
    int total = 0;
    while (getline(file,line))
    {
        if(line.length() != 0 && line.at(0) != '#')
        {
            cout << line << endl;
            value * v = newValue();
            v->line = line;
            push(s,v); 
        }
    }
}
