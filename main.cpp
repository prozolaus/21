#include "Orders_window.h"

//----------------------------------------------------------------------

int main()
try
{
    Point top_left{100, 100}; // will be top left corner of window
    Orders_window win{top_left, 900, 300, "Orders", "ex11_out.txt"};
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
