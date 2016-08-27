#pragma once
#include <string>

using namespace std;
class userBook
{
public:
	userBook();
	userBook(string ,int ,string );
	~userBook(void);
	string reBookName();
	string reISBN();
	int reListPosition();
	string ISBN;
	string bookName;
	int listPosition;
	userBook *next;
};