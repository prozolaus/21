// Chapter 21, exercise 9: define a class Order with members name (of customer),
// address, data and vector<Purchase>. Purchase is a class with members name
// (of product), unit_price and count. Define a mechanism for reading and
// writing Orders from and to a file and a mechanism to print Orders.
//
// Create a file of at least ten Orders, read it into a vector<Order>, sort it
// by name (of customer) and write it back out to file. Create another file of
// at least ten Orders of which about a third are the same as in the first file,
// read it into a list<Order>, sort it by address (of customer) and write it
// back out to file. Merge the two files into a third using std::merge().

// Remark: merge() requires two sorted ranges to work properly; also, it doesn't
// eliminate duplicates, which would make sense in this context. To do so, the
// Orders could either be added to a set<Order,Sort_by_name<Order>> first or
// they could be copied using unique_copy() or given to function unique().

// exercise 10: compute the total value of the orders in the two files (unit_price * count).

#include "Chrono.h" //class Date
#include <set>

using namespace Chrono;

class Purchase
{
    string name;
    double unit_price;
    int count;
    double sum;

public:
    Purchase() : name{""}, unit_price{0.0}, count{0}, sum{0} {}
    Purchase(const string &p_name, double p_price, int p_count)
        : name{p_name}, unit_price{p_price}, count{p_count}, sum{unit_price * count} {}
    const string &get_name() const { return name; }
    double get_price() const { return unit_price; }
    int get_count() const { return count; }
    double get_sum() const { return sum; }
};

class Order
{
    string name;
    string address;
    Date date_of_birth;
    vector<Purchase> purchases;

public:
    Order() = default;
    Order(const string &o_name, const string &o_address, const Date &o_birth_date, const vector<Purchase> o_purchases)
        : name{o_name}, address{o_address}, date_of_birth{o_birth_date}, purchases{o_purchases} {}
    const string &get_name() const { return name; }
    const string &get_address() const { return address; }
    const Date &get_date_of_birth() const { return date_of_birth; }
    const vector<Purchase> &get_purchases() const { return purchases; }
};

istream &operator>>(istream &is, Purchase &purch)
{
    string name, price, count;
    getline(is, name, '|');
    if (!is || name.empty())
        error("Cannot read a purchase name or value is empty!");
    name.pop_back(); // remove last space
    getline(is, price, '|');
    if (!is || price.empty())
        error("Cannot read a purchase price or value is empty!");
    istringstream ss{price};
    double d;
    ss >> d;
    if (!ss)
        error("Wrong price!");
    getline(is, count);
    if (!is || count.empty())
        error("Cannot read a purchase count or value is empty!");
    istringstream ss2{count};
    int i;
    ss2 >> i;
    if (!ss2)
        error("Wrong count!");
    purch = Purchase{name, d, i};
    return is;
}

istream &operator>>(istream &is, Order &ord)
{
    string name, addr, s;
    vector<Purchase> vp;
    getline(is, name);
    if (is.eof())
        return is;
    if (!is || name.empty())
        error("Cannot read a name or value is empty!");
    getline(is, addr);
    if (!is || addr.empty())
        error("Cannot read an address or value is empty!");
    Date date;
    is >> date;
    if (!is)
        error("Cannot read a date!");
    is.ignore(); // go to the end of the date line
    while (getline(is, s) && !s.empty())
    {
        istringstream iss{s};
        Purchase p;
        iss >> p;
        if (iss)
            vp.push_back(p);
    }
    ord = Order{name, addr, date, vp};
    return is;
}

ostream &operator<<(ostream &os, const Order &ord)
{
    os << ord.get_name() << endl
       << ord.get_address() << endl
       << ord.get_date_of_birth() << endl;
    for (const Purchase &p : ord.get_purchases())
        os << p.get_name() << " | " << p.get_price() << " | " << p.get_count() << endl;
    return os;
}

struct Orders_by_name
{
    bool operator()(const Order &ord1, const Order &ord2) const
    {
        return ord1.get_name() < ord2.get_name();
    }
};

bool sort_orders_by_address(const Order &ord1, const Order &ord2)
{
    return ord1.get_address() < ord2.get_address();
}

template <class Cont>
void get_orders_from_file(const string &filename, Cont &orders)
{
    ifstream ifs{filename};
    if (!ifs)
        error("Cannot open a file ", filename);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);
    Order order;
    while (ifs >> order)
        orders.push_back(order);
}

template <class Cont>
void write_orders_to_file(Cont &orders, const string &filename)
{
    ofstream ofs{filename};
    if (!ofs)
        error("Cannot open a file ", filename);
    ofs.exceptions(ofs.exceptions() | ios_base::badbit);
    for (const Order &o : orders)
        ofs << o << endl;
}

//----------------------------------------------------------------------

int main()
try
{
    vector<Order> orders1;
    list<Order> orders2;
    list<Order> merged_orders;
    Orders_by_name obn;

    string filenamein1 = "ex9_in1.txt", filenamein2 = "ex9_in2.txt",
           filenameout1 = "ex9_out1.txt", filenameout2 = "ex9_out2.txt",
           filenameout3 = "ex9_out3.txt", filenameout4 = "ex9_out4.txt";

    get_orders_from_file(filenamein1, orders1);
    get_orders_from_file(filenamein2, orders2);

    sort(orders1.begin(), orders1.end(), obn);
    orders2.sort(sort_orders_by_address);

    write_orders_to_file(orders1, filenameout1);
    write_orders_to_file(orders2, filenameout2);

    merged_orders.resize(orders1.size() + orders2.size());
    std::merge(orders1.begin(), orders1.end(), orders2.begin(), orders2.end(), merged_orders.begin(), obn);

    // eliminate duplicates and sort using set
    set<Order, Orders_by_name> merged_set(merged_orders.begin(), merged_orders.end());
    write_orders_to_file(merged_set, filenameout3);

    // eliminate duplicates and sort using unique() and resize()
    list<Order>::iterator it = unique(merged_orders.begin(), merged_orders.end(),
                                      [](const Order &ord1, const Order &ord2)
                                      { return ord1.get_name() == ord2.get_name(); });
    merged_orders.resize(distance(merged_orders.begin(), it));
    merged_orders.sort(obn);
    write_orders_to_file(merged_orders, filenameout4);

    // filenameout3 == filenameout4

    //ex10
    double gensum = 0;
    for (const Order &order : merged_orders)
        for (const Purchase &purchases : order.get_purchases())
            gensum += purchases.get_sum();
    cout << gensum << endl;
}
catch (Chrono::Date::Invalid &ie)
{
    cerr << "Invalid date!\n";
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
