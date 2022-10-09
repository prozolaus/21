#include "punct_stream.h"

//--------------------------------------------------------

Punct_stream& Punct_stream::operator>>(string& s)
{
    while (!(buffer >> s))
    {
        if (buffer.bad() || !source.good())
            return *this;
        buffer.clear();

        string line;
        getline(source, line);

        for (char& ch : line)
            if (is_whitespace(ch))
                ch = ' ';
            else if (!sensitive)
                ch = tolower(ch);

        buffer.str(line);
    }
    return *this;
}

//--------------------------------------------------------

bool Punct_stream::is_whitespace(char ch)
{
    for (char w : white)
        if (ch == w)
            return true;
    return false;
}

//--------------------------------------------------------

Punct_stream::operator bool()
{
    return !(source.fail() || source.bad()) && source.good();
}

//--------------------------------------------------------

