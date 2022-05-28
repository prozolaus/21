#include "std_lib_facilities.h"

//----------------------------------------------------------------------

template <typename T>
struct Larger_than
{
    Larger_than(const T &x) : d{x} {}
    bool operator()(const T &t) const { return t < d; }

private:
    T d;
};

template <typename T>
void print_vec(const vector<T> &vec)
{
    for (const T &d : vec)
        cout << d << "\n";
    cout << "\n";
}

//----------------------------------------------------------------------

int main()
try
{
    // 3.1
    string filename{"doubles.txt"};
    ifstream ifs{filename};
    if (!ifs)
        error("Cannot open file ", filename);
    istream_iterator<double> ii{ifs};
    istream_iterator<double> eos;
    vector<double> vd{ii, eos};

    // 3.2
    cout << "vd:\n";
    print_vec(vd);

    // 3.3
    vector<int> vi{vd.begin(), vd.end()};

    // 3.4
    cout << "pairs (vd[i], vi[i]):\n";
    for (int i = 0; i < vd.size(); i++)
        cout << '(' << vd[i] << ", " << vi[i] << ')' << "\n";

    // 3.5
    double sum = accumulate(vd.begin(), vd.end(), 0.0);
    cout << "\nSum of vd-elements: " << sum << "\n\n";

    // 3.6
    cout << "Sum difference: ";
    cout << sum - accumulate(vi.begin(), vi.end(), 0) << "\n\n";

    // 3.7
    cout << "vd after reverse:\n";
    reverse(vd.begin(), vd.end());
    print_vec(vd);

    // 3.8
    double average = sum / vd.size();
    cout << "Arithmetical mean: " << average << "\n\n";

    // 3.9
    int count = count_if(vd.begin(), vd.end(), Larger_than{average});
    vector<double> vd2(count);
    copy_if(vd.begin(), vd.end(), vd2.begin(), Larger_than{average});
    
    // 3.10
    sort(vd2.begin(), vd2.end());
    cout << "vd2:\n";
    print_vec(vd2);
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
