#include "std_lib_facilities.h"

struct Record
{
    double unit_price;
    int units;
};

double price(double v, const Record &r)
{
    return v + r.unit_price * r.units;
}

void f(const vector<Record> &vr)
{
    double total = accumulate(vr.begin(), vr.end(), 0.0, price);
    cout << total << endl;
}

//----------------------------------------------------------------------

int main()
try
{
    array<double, 4> a = {1.1, 2.2, 3.3, 4.4};
    cout << accumulate(a.begin(), a.end(), 0.0) << endl;
    cout << accumulate(a.begin(), a.end(), 1.0, multiplies<double>{}) << endl;

    vector<Record> v{{50.0, 1}, {60.0, 2}, {70.0, 3}, {80.0, 4}};
    f(v);
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
