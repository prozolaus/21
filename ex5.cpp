#include "std_lib_facilities.h"

template <class InputIterator, class T>
int mycount(InputIterator first, InputIterator last, const T &val)
{
    int cnt = 0;
    if (last == first - 1 || last == first && &*first == nullptr) // container is empty
        return cnt;
    do
    {
        if (*first == val)
            ++cnt;
    } while (first++ != last);
    return cnt;
}

//----------------------------------------------------------------------

template <class Iterator, class T>
Iterator myfind(Iterator first, Iterator last, const T &val)
{
    if (last == first - 1 || last == first && &*first == nullptr) // container is empty
        return first;
    do
    {
        if (*first == val)
            break;
    } while (first++ != last);
    return first;
}

//----------------------------------------------------------------------

int main()
try
{
    int a[20] = {1, 2, 3, 4, 5, 6, 7, 7, 7, 8, 9, 9, 11, 11, 12, 16, 20, 20, 20, 20};
    int cnt1 = mycount(a, a + 19, 20);
    cout << "mycount1: " << cnt1 << ". ";
    auto pa = myfind(a, a + 19, 20);
    cout << ((pa == a + 20) ? "Not found!\n" : "Found!\n");

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 7, 7, 8, 9, 9, 11, 11, 12, 16, 20, 20, 20, 20};
    int cnt2 = mycount(v.begin(), v.end() - 1, 20);
    cout << "mycount2: " << cnt2 << ". ";
    auto pv = myfind(v.begin(), v.end() - 1, 20);
    cout << ((pv == v.end()) ? "Not found!\n" : "Found!\n");

    int ea[0]; // empty static array
    int cnt3 = mycount(ea, ea, 20);
    cout << "mycount3: " << cnt3 << ". ";
    auto pea = myfind(ea, ea, 20);
    cout << ((pea == ea + 1) ? "Not found!\n" : "Found!\n");

    vector<int> ev; // empty vector
    int cnt4 = mycount(ev.begin(), ev.end() - 1, 1);
    cout << "mycount4: " << cnt4 << ". ";
    auto pev = myfind(ev.begin(), ev.end() - 1, 1);
    cout << ((pev == ev.end()) ? "Not found!\n" : "Found!\n");

    vector<int> ev2; // empty vector2
    int cnt5 = std::count(ev2.begin(), ev2.end(), 20);
    cout << "std::count: " << cnt5 << ". ";
    auto pev2 = std::find(ev2.begin(), ev2.end(), 1);
    cout << ((pev2 == ev2.end()) ? "Not found!\n" : "Found!\n");
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
