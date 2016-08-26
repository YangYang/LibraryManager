#pragma once
#include <string>

using namespace std;
class Book
{
public:
	Book();
	Book(string ,int );
	~Book(void);
	string reISBN();
	int reListPosition();
	string ISBN;
	int listPosition;
	Book *next;
};