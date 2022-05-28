#include "std_lib_facilities.h"

istream &operator>>(istream &is, map<string, int> &msi)
{
    string s;
    int i;
    if (is >> s >> i)
        msi.insert(pair<string, int>{s, i});
    else
        error("Input data is wrong!");
    return is;
}

template <typename T>
struct Map_to_add
{
    T operator()(T &i, const pair<string, T> &x)
    {
        return i + x.second;
    }
};

template <typename T1, typename T2>
void print(const map<T1, T2> &m)
{
    cout << setw(13) << left << "Key\t"
         << "Value" << endl;
    cout << "--------------------------\n";

    for (const auto &i : m)
        cout << setw(13) << left << i.first << "\t" << i.second << endl;
    cout << "--------------------------\n";

    if (m.empty())
        cout << "Container is empty!\n";
}

//----------------------------------------------------------------------

int main()
try
{
    map<string, int> msi;
    string filename{"items2.txt"};
    ifstream ifs{filename};
    if (!ifs)
        error("Cannot open file ", filename);
    for (int i = 0; i < 10; i++)
        ifs >> msi;
    msi.erase("Lime");
    msi.erase("Pear");
    msi["Passion fruit"] = 300;
    msi["Avocado"] = 220;
    print(msi);
    int sum = accumulate(msi.begin(), msi.end(), 0, Map_to_add<int>{});
    cout << setw(13) << left << "Sum:\t" << sum << "\n\n";

    map<int, string> mis;
    for (const auto &p : msi)
        mis.insert(pair<int, string>{p.second, p.first});
    print(mis);
    
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
