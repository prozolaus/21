#include "std_lib_facilities.h"

//----------------------------------------------------------------------

int main()
try
{
    string from, to, to2;
    cin >> from >> to >> to2;

    ifstream is{from};
    ofstream os{to};
    ofstream os2{to2};

    istream_iterator<string> ii{is};
    istream_iterator<string> eos;
    ostream_iterator<string> oo{os, "\n"};
    ostream_iterator<string> oo2{os2, "\n"};

    vector<string> b{ii, eos};
    sort(b.begin(), b.end());
    copy(b.begin(), b.end(), oo);

    //version strongly discouraged
    vector<string> b2{300};
    copy(ii, eos, b2.begin());
    sort(b2.begin(), b2.end());
    copy(b2.begin(), b2.end(), oo2);

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
