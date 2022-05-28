#include "std_lib_facilities.h"

struct Item
{
    Item() : name{""}, iid{0}, value{0.0} {}
    Item(string s, int i, double d) : name{s}, iid{i}, value{d} {}
    string name;
    int iid;
    double value;
};

istream &operator>>(istream &is, Item &vi)
{
    string s;
    int i;
    double d;
    if (is >> s >> i >> d)
        vi = Item{s, i, d};
    else
        error("Input data is wrong!");
    return is;
}

template <typename Cont>
void print(const Cont &vi)
{
    cout << setw(10) << "Name\t"
         << "ID\t"
         << "Value" << endl;
    cout << "-----------------------------------------\n";

    for (const Item &i : vi)
        cout << setw(10) << i.name << "\t" << i.iid << "\t" << i.value << endl;

    if (vi.empty())
        cout << "Container is empty!\n";
}

struct by_name
{
    bool operator()(const Item &i1, const Item &i2) const
    {
        return i1.name < i2.name;
    }
};

struct by_id
{
    bool operator()(const Item &i1, const Item &i2) const
    {
        return i1.iid < i2.iid;
    }
};

bool by_value(const Item &i1, const Item &i2)
{
    return i1.value > i2.value;
};

template <typename Cont>
bool find_and_erase_by_name(Cont &vi, const string &s)
{
    auto p = find_if(vi.begin(), vi.end(), [&](const Item &i)
                     { return i.name == s; });
    if (p == vi.end())
        return false;
    vi.erase(p);
    return true;
}

template <typename Cont>
bool find_and_erase_by_id(Cont &vi, int id)
{
    auto p = find_if(vi.begin(), vi.end(), [&](const Item &i)
                     { return i.iid == id; });
    if (p == vi.end())
        return false;
    vi.erase(p);
    return true;
}

//----------------------------------------------------------------------

int main()
try
{
    // 1.1
    list<Item> vi;
    string filename{"items.txt"};
    ifstream ifs{filename};
    if (!ifs)
        error("Cannot open file ", filename);
    Item item;
    for (int i = 0; i < 10; i++)
        if (ifs >> item) 
            vi.insert(vi.end(), item);

    // 1.2
    // sort(vi.begin(), vi.end(), by_name{});
    // when vi is a list
    // vi.sort(by_name{});

    // 1.3
    // sort(vi.begin(), vi.end(), by_id{});
    // when vi is a list
    // vi.sort(by_id{});

    // 1.4
    // sort(vi.begin(), vi.end(), by_value);
    // when vi is a list
    // vi.sort(by_value);

    // 1.5
    vi.push_back(Item{"horse shoe", 99, 12.34});
    vi.push_back(Item{"Canon S400", 9988, 499.95});

    // 1.6
    find_and_erase_by_name(vi, "Lime");
    find_and_erase_by_name(vi, "Mango");

    // 1.7
    find_and_erase_by_id(vi, 9);
    find_and_erase_by_id(vi, 10);

    print(vi);
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
