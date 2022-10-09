#pragma once

#include "std_lib_facilities.h"

//--------------------------------------------------------

class Punct_stream
{
public:
    Punct_stream(istream& is)
        : source{ is }, sensitive{ true } {}

    void whitespace(const string& s) { white = s; }
    void add_white(char c) { white += c; }
    bool is_whitespace(char c);

    void case_sensitive(bool b) { sensitive = b; }
    bool is_case_sensitive() { return sensitive; }

    Punct_stream& operator>>(string& s);
    operator bool();

private:
    istream& source;
    istringstream buffer;
    string white;
    bool sensitive;
};

//--------------------------------------------------------
