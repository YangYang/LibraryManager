#pragma once
#include <string>

using namespace std;
class Book
{
public:
	Book();
	Book(string ,string );
	~Book(void);
	string reISBN();
	string reListPosition();
	string ISBN;
	string listPosition;
	Book *next;
};