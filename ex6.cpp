// Chapter 21, exercise 6: 
// implement the Fruit example (set) using a
// set<Fruit*,Fruit_comparison> (pointers instead of copies)
// i.e., define a comparison operation for Fruit*

#include "std_lib_facilities.h"
#include <set>

struct Fruit
{
    string name;
    int count;
    double unit_price;
};
//----------------------------------------------------------------------

struct Fruit_order_by_name
{
    bool operator()(const Fruit *fruit1, const Fruit *fruit2) const
    {
        return fruit1->name < fruit2->name;
    }
};
//----------------------------------------------------------------------

ostream &operator<<(ostream &os, const Fruit *fruit)
{
    cout << "Fruit: " << fruit->name << ", count: " << fruit->count << ", price: " << fruit->unit_price;
    return os;
}

//----------------------------------------------------------------------

int main()
try
{
    set<Fruit *, Fruit_order_by_name> inventory;
    inventory.insert(new Fruit{"quince", 5});
    inventory.insert(new Fruit{"apple", 200, 0.37});
    for (auto p = inventory.begin(); p != inventory.end(); ++p)
        cout << *p << endl;
    // cleaning up
    for (auto p = inventory.begin(); p != inventory.end(); ++p)
        delete *p;
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
