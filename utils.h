//---------------------------------------------------------------------------
#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <cstdarg>
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <map>
//---------------------------------------------------------------------------
using namespace std;
typedef map<string, AnsiString, less<string>, allocator<string> > stmap;
//---------------------------------------------------------------------------

void split(TStringList*, char*, const char*);
string format(const char*, ...);
string get_filebody(char*);

#endif
