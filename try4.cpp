#include "std_lib_facilities.h"
#include <set>

//----------------------------------------------------------------------

int main()
try
{
    string from, to;
    cin >> from >> to;

    ifstream is{from};
    ofstream os{to};

    set<string> b{istream_iterator<string>{is}, istream_iterator<string>{}};

    copy(b.begin(), b.end(), ostream_iterator<string>{os, "\n"});
}
catch (Range_error &re)
{
    cerr << "Bad index: " << re.index << "\n";
}
catch (const std::exception &e)
{
    cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Some kind of exception\n";
    return 2;
}
