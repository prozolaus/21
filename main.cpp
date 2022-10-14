// Chapter 21, exercise 15: provide a GUI for exercise 14

#include "Words_window_ex15.h"

int main()
try
{
	Words_window ww{ Point{300,100}, 800, 600, "Chapter 21. Exercise 15. " };
	return gui_main();	
}
catch (const std::exception& e)
{
	cerr << "Exception: " << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "Some kind of exception\n";
	return 2;
}
