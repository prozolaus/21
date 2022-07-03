#include "std_lib_facilities.h"

template <class InputIterator, class T>
int mycount(InputIterator first, InputIterator last, const T &val)
{
    int cnt = 0;
    while (first != last)
    {
        if (*first == val)
            ++cnt;
        ++first;
    }
    return cnt;
}

//----------------------------------------------------------------------

int main()
try
{
    int a[20] = {1, 2, 3, 4, 5, 6, 7, 7, 7, 8, 9, 9, 11, 11, 12, 16, 20, 20, 20, 20};
    int cnt = std::count(a, a + 20, 9);
    int cnt2 = mycount(a, a + 20, 9);
    cout << "std::count: " << cnt << ", mycount: " << cnt2 << endl;
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
