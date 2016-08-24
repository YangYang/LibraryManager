#include "StdAfx.h"
#include "TransformPlus.h"


TransformPlus::TransformPlus(void)
{
}


TransformPlus::~TransformPlus(void)
{
}

//CString
CString TransformPlus::toCString(string str){
	CString cstr(str.c_str());
	return cstr;
}

CString TransformPlus::toCString(double dbl){
	CString t;
	t.Format(L"%f",dbl);
	return t;
}

CString TransformPlus::toCString(int i){
	CString t;
	t.Format(L"%d",i);
	return t;
}


//String
string TransformPlus::toString(CString cstr){
	USES_CONVERSION;
	string str = T2A(( cstr.GetBuffer()));
	return str;
}

string TransformPlus::toString(double dbl){
	char buffer[20];
	sprintf_s(buffer, "%f", dbl);
	string str = buffer;
	return buffer;
}

string TransformPlus::toString(int i){
	char str[8]; 
	int length = sprintf(str, "%05X", i); 
	return str;
}

string TransformPlus::toString(TCHAR *STR){
	int iLen = WideCharToMultiByte(CP_ACP, 0,STR, -1, NULL, 0, NULL, NULL);
	char* chRtn =new char[iLen*sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
	string str(chRtn);
	return str;
}

string TransformPlus::toString(char* c){
	string s(c);
	return s;
}

//double
double TransformPlus::toDouble(CString cstr){
	return _wtof(cstr);
}

double TransformPlus::toDouble(string str){
	double value = atof(str.c_str());
	return value;
}

double TransformPlus::toDouble(int i){
	double dbl = (double)i;
	return dbl;
}


//int
int TransformPlus::toInt(CString cstr){
	int i = _ttoi(cstr);
	return i;
}

int TransformPlus::toInt(string str){
	int n = atoi(str.c_str());
	return n;
}

int TransformPlus::toInt(double dbl){
	int i = (int)dbl;
	return i;
}

const char* toConstChar(string s){
	return s.c_str();
}

