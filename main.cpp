// Chapter 21, exercise 12 : provide a GUI for querying a file of Orders.

#include "Orders_window_ex12.h"

//----------------------------------------------------------------------

int main()
try
{
    Point top_left{100, 100}; // will be top left corner of window
    Orders_window win{top_left, 900, 600, "Orders"};
    return gui_main();
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
