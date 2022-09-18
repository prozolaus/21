
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#pragma once

#include "GUI.h" // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"
#include "Orders.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Orders_window : Graph_lib::Window
{
    Orders_window(Point xy, int w, int h, const string &title)
        : Window(xy, w, h, title),
        out_box{ Point {10, 30},  w - 300, h - 40, ""},
        fname_box{ Point{x_max() - 150, 50}, 150, 20, "Filename:" },
        cname_box{ Point{x_max() - 150, 150}, 150, 20, "Client name:" },
        sum_box{ Point{x_max() - 100, 100}, 100, 20, "" },
        all_orders_button{ Point{x_max() - 150, 70}, 150, 20, "Show all orders", [](Address, Address pw)
            {
                reference_to<Orders_window>(pw).show_orders();
            } },
        sum_button{ Point{x_max() - 260, 100}, 160, 20, "The sum of all orders -> ", [](Address, Address pw)
            {
                reference_to<Orders_window>(pw).orders_sum();
            } },
        by_name_button{ Point{x_max() - 150, 170}, 150, 20, "Show orders by name", [](Address, Address pw)
            {
                reference_to<Orders_window>(pw).orders_by_name();
            } },
        quit_button{Point{x_max() - 70, 0}, 70, 20, "Exit", [](Address, Address pw)
                      {
                          reference_to<Orders_window>(pw).quit();
					  } },
        name_error_status{ Point{10, 20}, ""}
	{
        attach(out_box);
        attach(fname_box);
        attach(cname_box);
        attach(sum_box);
        attach(all_orders_button);
        attach(sum_button);
        attach(by_name_button);
        attach(quit_button);
        attach(name_error_status);
        name_error_status.set_color(Color::red);
    }

private:

    string filename, clientname;
    vector<Order> vo;
    Button all_orders_button, sum_button, by_name_button, quit_button;
    Multiline_out_box out_box;
    In_box fname_box, cname_box;
    Out_box sum_box;
    Text name_error_status;
    bool get_orders_and_check();
    void show_orders();
    void orders_sum();
    void orders_by_name();
    void quit() { Window::hide(); }
};

//------------------------------------------------------------------------------

bool Orders_window::get_orders_and_check()
{
    name_error_status.set_label("");
    filename = fname_box.get_string();
    try
    {
        get_orders_from_file(filename, vo);
    }
    catch (const std::exception& e)
    {
        name_error_status.set_label(e.what());
        redraw();
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------

void Orders_window::show_orders()
{
    if (!get_orders_and_check())
        return;
    ostringstream oss;
    for (const Order& o : vo)
        oss << o << endl;
    out_box.put(oss.str());
    redraw();
    vo.clear();
}

//------------------------------------------------------------------------------

void Orders_window::orders_sum()
{
    if (!get_orders_and_check())
        return;
    double sum = 0.0;
    for (const Order& o : vo)
        sum += o.get_order_sum();
    ostringstream oss;
    oss << sum;
    sum_box.put(oss.str());
    redraw();
    vo.clear();
}

//------------------------------------------------------------------------------

void Orders_window::orders_by_name()
{
    if (!get_orders_and_check())
        return;
    clientname = cname_box.get_string();
    ostringstream oss;
    for (const Order& o : vo)
        if (o.get_name() == clientname)
            oss << o << endl;
    out_box.put(oss.str());
    redraw();
    vo.clear();
}

//------------------------------------------------------------------------------

