#include <vcl.h>
//---------------------------------------------------------------------------
#pragma hdrstop

#include "utils.h"

#pragma package(smart_init)

//---------------------------------------------------------------------------
// Split the string by the given separator

void split(TStringList* lout, char* str, const char* separator)
{
    for(char* tok = strtok(str, separator); tok; tok = strtok(NULL, separator))
        lout->Add(AnsiString(tok).Trim());
}

//---------------------------------------------------------------------------
// Missing string printf
// This is safe and convenient but not exactly efficient

string format(const char* fmt, ...)
{
    int size = 512;
    char* buffer = 0;
    buffer = new char[size];
    va_list vl;
    va_start(vl, fmt);
    int nsize = vsnprintf(buffer, size, fmt, vl);
    if (size <= nsize) //fail delete buffer and try again
    {
        delete[] buffer;
        buffer = 0;
        buffer = new char[nsize+1]; //+1 for /0
        nsize = vsnprintf(buffer, size, fmt, vl);
    }
    string ret(buffer);
    va_end(vl);
    delete[] buffer;
    return ret;
}

//---------------------------------------------------------------------------
// Get file body content

string get_filebody(char* file)
{
    fstream fstr;
    streambuf * pbuf;
    bool isError = false;

    try
    {
        fstr.open(file, std::fstream::in);
        pbuf = fstr.rdbuf();
    }
    catch (std::exception& e)
    {
        isError = true;
    }

    size_t size = pbuf->pubseekoff(0, fstr.end);
    if (isError || size == 0)
        return "";

    pbuf->pubseekoff(0, fstr.beg);
    ostringstream ss;
    ss << pbuf;

    fstr.close();
    return ss.str();
}
//---------------------------------------------------------------------------

