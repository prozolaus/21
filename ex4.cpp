#include "std_lib_facilities.h"

template <class InputIterator, class Pred>
int mycount_if(InputIterator first, InputIterator last, Pred pred)
{
    int cnt = 0;
    while (first != last)
    {
        if (pred(*first))
            ++cnt;
        ++first;
    }
    return cnt;
}

//----------------------------------------------------------------------

template <class T>
struct Bigger_than
{
    Bigger_than(T tt) : t{tt} {}
    bool operator()(const T &val) { return val > t; }
    T t;
};

//----------------------------------------------------------------------

int main()
try
{
    int a[20] = {1, 2, 3, 4, 5, 6, 7, 7, 7, 8, 9, 9, 11, 11, 12, 16, 20, 20, 20, 20};
    int x = 10;
    int cnt = std::count_if(a, a + 20, [&](int i)
                            { return i > x; });
    int cnt2 = mycount_if(a, a + 20, [&](int i)
                          { return i > x; });
    int cnt3 = mycount_if(a, a + 20, Bigger_than{x});
    cout << "std::count_if (lambda): " << cnt
         << ", mycount_if (lambda): " << cnt2
         << ", mycount_if (func obj): " << cnt3 << endl;
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
