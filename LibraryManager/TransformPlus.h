#include<cstring>
#include <cstringt.h>
#include<string>
using namespace std;
#pragma once
/**
 * C++ (int , double , string , CString)互转类
 * @author shianqi@imudges.com
 * 适用于vs2010
 */
class TransformPlus
{
public:
	TransformPlus(void);
	~TransformPlus(void);
	//CString
	CString toCString(string str);
	CString toCString(double dbl);
	CString toCString(int i);

	//string
	string toString(CString cstr);
	string toString(double dbl);
	string toString(int i);
	string toString(TCHAR *STR);
	string toString(char* c);

	//double
	double toDouble(CString cstr);
	double toDouble(string str);
	double toDouble(int i);

	//int
	int toInt(CString cstr);
	int toInt(string str);
	int toInt(double dbl);
	long toLong(CString cstr);
	//const char*
	
};

