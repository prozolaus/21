// Chapter 21, exercise 8:
// take word frequency example from 21.6.1 and modify it
// to output its lines in order of frequency rather than lexicographical order
// ("3: C++" rather than "C++: 3")

#include "std_lib_facilities.h"

int main()
try
{
    map<string, int> words;
    ifstream ifs{"ex8.txt"};
    if (!ifs)
        error("Cannot open a file");
    for (string s; ifs >> s;)
        ++words[s];

    multimap<int, string> mwords;
    for (const auto &w : words)
        mwords.insert(make_pair(w.second, w.first));

    for (const auto &mw : mwords)
        cout << mw.first << ": " << mw.second << endl;
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
