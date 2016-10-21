#include <iostream>
#include <fstream>
using namespace std;

// Utilities
bool equals(string,string);
string before(string, string);
string after(string, string);

// Prices
struct Prices;
Prices * newPrices();
void addPrice(Prices*, string, string);

// People
struct People;
People * newPeople();
void pushValue(People*,Prices*,string,string);
void handleOperator(People*, string, char);
void handleDiscount(People*, string, string);
void handleClose(People*,string);
int getTotal(People*,string);

// LineSplit
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

lineSplit * split(string line)
{
	lineSplit * split = newLineSplit();
	
	split->name = before(line, "\t");
	split->op = before(after(line, "\t"), "\t");
	split->value = after(after(line, "\t"), "\t");
	
	return split;
}

// TypeStatement
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

type_statement getTypeStatement(lineSplit * sp)
{
	string op = sp->op;
	string name = sp->name;
	if(equals(op,"open")) 		return open;
	if(equals(op,"close")) 		return close;
	if(equals(op,"buy")) 		return buy;
	if(equals(op,"add")) 		return add;
	if(equals(op,"times")) 		return times;
	if(equals(op,"discount%")) 	return discount;
	if(equals(op,"total")) 		return total;
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
				case price: addPrice(prices, s->op, s->value);
							break;
				case buy:	pushValue(people, prices, s->name, s->value);
							break;
				case open:	handleOperator(people, s->name, '(');
							break;
				case close:	handleClose(people, s->name);
							break;
				case add:	handleOperator(people, s->name, '+');
                            pushValue(people, prices, s->name, s->value);
							break;
				case times:	handleOperator(people, s->name, '*');
                            pushValue(people, prices, s->name, s->value);
							break;
				case discount:
                            handleDiscount(people, s->name, s->value);
							break;
				case total:	cout << getTotal(people,s->name) << endl;
							break;
				
			}
        }
    }
}
 
