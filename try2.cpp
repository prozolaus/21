#include "std_lib_facilities.h"

double weighted_value(const pair<string, double> &a, const pair<string, double> &b)
{
    return a.second * b.second;
}

//----------------------------------------------------------------------

int main()
try
{
    map<string, double> dow_price = {
        {"MSFT", 272.99},
        {"CRM", 171.43},
        {"AAPL", 161.50},
        {"INTC", 46.45},
    };
    map<string, double> dow_weight = {
        {"MSFT", 5.317162},
        {"CRM", 3.355865},
        {"AAPL", 3.151177},
        {"INTC", 0.899417},
    };
    map<string, string> dow_name = {
        {"MSFT", "Microsoft Corporation"},
        {"CRM", "Salesforce Inc."},
        {"AAPL", "Apple Inc."},
        {"INTC", "Intel Corporation"},
    };

    double apple_price = dow_price["AAPL"];
    double dji_index = inner_product(dow_price.begin(), dow_price.end(),
                                     dow_weight.begin(), 0.0,
                                     plus<double>{}, weighted_value);

    for (const auto &p : dow_price)
    {
        const string &symbol = p.first;
        cout << symbol << '\t' << p.second << '\t' << dow_name[symbol] << endl;
    }
    cout << "DJI = " << dji_index << endl;
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
