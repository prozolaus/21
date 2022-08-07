
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
    Orders_window(Point xy, int w, int h, const string &title, const string &filename)
        : Window(xy, w, h, title),
          filenameout{filename},
          name{Point{100, 10}, 250, 20, "Name: "},
          address{Point{100, 30}, 600, 20, "Address: "},
          date{Point{100, 50}, 90, 20, "Date: "},
          purchases{Point{100, 70}, 600, 100, "Purchase: "},
          order_add_button{Point{x_max() - 500, 0}, 200, 20, "Add order and clear fields", [](Address, Address pw)
                           {
                               reference_to<Orders_window>(pw).add_order();
                           }},
          quit_button{Point{x_max() - 250, 0}, 150, 20, "Save orders to file", [](Address, Address pw)
                      {
                          reference_to<Orders_window>(pw).save();
                      }},
          quit_button2{Point{x_max() - 70, 0}, 70, 20, "Exit", [](Address, Address pw)
                       {
                           reference_to<Orders_window>(pw).quit();
                       }}
    {
        attach(name);
        attach(address);
        attach(date);
        attach(purchases);
        attach(order_add_button);
        attach(quit_button);
        attach(quit_button2);
    }
    void test();

private:
    vector<Order> orders;
    string filenameout;
    In_box name;
    In_box address;
    In_box date;
    Multiline_in_box purchases;
    Button order_add_button;
    Button quit_button, quit_button2;

    void add_order();
    void save() { write_orders_to_file(orders, filenameout); }
    void quit() { Window::hide(); }
};

//------------------------------------------------------------------------------
void Orders_window::add_order()
{
    string nm, addr, ps, s;
    Date dt;
    vector<Purchase> vp;
    nm = name.get_string();
    if (nm.empty())
    {
        name.put("Fill the name");
        return;
    }
    addr = address.get_string();
    if (addr.empty())
    {
        address.put("Fill the address");
        return;
    }
    istringstream iss{date.get_string()};
    iss >> dt;
    if (!iss)
    {
        date.put("Fill the date");
        return;
    }
    ps = purchases.get_string();
    istringstream iss2{ps};
    while (getline(iss2, s) && !s.empty())
    {
        istringstream issm{s};
        Purchase p;
        issm >> p;
        if (issm)
            vp.push_back(p);
        else
        {
            purchases.put("Fill purchases correctly");
            return;
        }
    }
    if (vp.size() != 0)
        orders.push_back(Order{nm, addr, dt, vp});
    else
    {
        purchases.put("Fill purchases");
        return;
    }
    name.put("");
    address.put("");
    date.put("");
    purchases.put("");
}
//------------------------------------------------------------------------------
