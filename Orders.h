#pragma once

#include "Chrono.h" //class Date

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
    double get_order_sum() const;
};

//----------------------------------------------------------------------

double Order::get_order_sum() const
{
    double sum = 0.0;
    for (const Purchase& p : purchases)
        sum += p.get_sum();
    return sum;
}

//----------------------------------------------------------------------

istream &operator>>(istream &is, Purchase &purch)
{
    string name, price, count;
    getline(is, name, '|');
    if (!is || name.empty())
        return is;
    name.pop_back(); // remove last space
    getline(is, price, '|');
    if (!is || price.empty())
        return is;
    istringstream ss{price};
    double d;
    ss >> d;
    if (!ss)
    {
        is.clear(ios_base::failbit);
        return is;
    }
    getline(is, count);
    if (!is || count.empty())
        return is;
    istringstream ss2{count};
    int i;
    ss2 >> i;
    if (!ss2)
    {
        is.clear(ios_base::failbit);
        return is;
    }
    purch = Purchase{name, d, i};
    return is;
}

//----------------------------------------------------------------------

istream& operator>>(istream& is, Order& ord)
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
        istringstream iss{ s };
        Purchase p;
        iss >> p;
        if (iss)
            vp.push_back(p);
    }
    ord = Order{ name, addr, date, vp };
    return is;
}

//----------------------------------------------------------------------

template <class Cont>
void get_orders_from_file(const string& filename, Cont& orders)
{
    ifstream ifs{ filename };
    if (!ifs)
        error("Cannot open a file ", filename);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);
    Order order;
    while (ifs >> order)
        orders.push_back(order);
}

//----------------------------------------------------------------------

ostream &operator<<(ostream &os, const Order &ord)
{
    os << ord.get_name() << endl
       << ord.get_address() << endl
       << ord.get_date_of_birth() << endl;
    for (const Purchase &p : ord.get_purchases())
        os << p.get_name() << " | " << p.get_price() << " | " << p.get_count() << endl;
    return os;
}

//----------------------------------------------------------------------

struct Orders_by_name
{
    bool operator()(const Order &ord1, const Order &ord2) const
    {
        return ord1.get_name() < ord2.get_name();
    }
};

//----------------------------------------------------------------------

bool sort_orders_by_address(const Order &ord1, const Order &ord2)
{
    return ord1.get_address() < ord2.get_address();
}

//----------------------------------------------------------------------

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
