#include <iostream>
using namespace std;

char priority [4] = { '+', '-', '*', '/' };

string before(string s, string b)
{
    return s.substr(0,s.find(b));
}

string after(string s, string b)
{
    return s.substr(s.find(b)+1);
}

bool equals(string s1, string s2)
{
	return s1.compare(s2) == 0;
}

bool isNumber(char c)
{
	return (int)c > 47 && (int)c < 58;
}

bool isNumber(string s)
{
	for(int x = 0; x < s.length(); x++)
	{
		if(!isNumber(s.at(x)))
		{
			return false;
		}
	}
	
	return true;
}

int getPriority(char c)
{
	for(int x = 0; x < 4; x++)
	{
		if(priority[x] == c)
		{
			return x;
		}
	}
	
	return -1;
}
