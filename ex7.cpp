// Chapter 21, exercise 7:
// implement and test binary search for a vector<int> and a list<string>

#include "std_lib_facilities.h"

template <class Iterator, class T>
bool my_binary_search(Iterator first, Iterator last, const T &val)
{
    int n = distance(first, last) / 2;
    Iterator pos = first;
    advance(pos, n);

    if (val == *pos)
        return true;

    if (val < *pos)
        last = pos;
    else
        first = ++pos;

    if (first == last)
        return false;

    return my_binary_search(first, last, val);
}

//----------------------------------------------------------------------

int main()
try
{
    //vector<int> v{1, 2, 3, 4, 5}; // must be sorted
    list<int> v{1, 2, 3, 4, 5}; // must be sorted
    for (int i = 0; i < v.size() + 2; i++)
    {
        cout << "i = " << i << endl;
        bool b = std::binary_search(v.begin(), v.end(), i);
        bool b2 = my_binary_search(v.begin(), v.end(), i);
        cout << "std::binary: " << (b ? "Found\n" : "Not found\n");
        cout << "my_binary:   " << (b2 ? "Found\n" : "Not found\n");
    }
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
