
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
          status{Point{100, 200}, ""},
          name{Point{100, 10}, 250, 20, "Name: "},
          address{Point{100, 30}, 600, 20, "Address: "},
          date{Point{100, 50}, 100, 20, "Date: "},
          purchases{Point{100, 70}, 600, 100, "Purchase: "},
          order_add_button{Point{x_max() - 500, 0}, 200, 20, "Add order and clear fields", [](Address, Address pw)
                           {
                               reference_to<Orders_window>(pw).add_order();
                           }},
          save_button{Point{x_max() - 250, 0}, 150, 20, "Save orders to file", [](Address, Address pw)
                      {
                          reference_to<Orders_window>(pw).save();
                      }},
          quit_button{Point{x_max() - 70, 0}, 70, 20, "Exit", [](Address, Address pw)
                      {
                          reference_to<Orders_window>(pw).quit();
                      }},
          orders_box{Point{100, 250}, 30, 20, "Orders: "}, orders_count{0}
    {
        attach(status);
        status.set_color(Color::red);
        attach(name);
        attach(address);
        attach(date);
        attach(purchases);
        attach(order_add_button);
        attach(save_button);
        attach(quit_button);
        attach(orders_box);
        orders_box.put("0");
    }

private:
    vector<Order> orders;
    string filenameout;
    In_box name;
    In_box address;
    In_box date;
    Multiline_in_box purchases;
    Button order_add_button;
    Button save_button, quit_button;
    Text status;
    Out_box orders_box;
    int orders_count;

    void add_order();
    void clear_fields();
    void save() { write_orders_to_file(orders, filenameout); }
    void quit() { Window::hide(); }
};

//------------------------------------------------------------------------------
void Orders_window::add_order()
{
    string nm, addr, ps, s;
    Date dt;
    vector<Purchase> vp;
    if (!status.label().empty())
    {
        status.set_label("");
        redraw();
    }
    nm = name.get_string();
    if (nm.empty())
    {
        name.put("Fill in the name");
        return;
    }
    addr = address.get_string();
    if (addr.empty())
    {
        address.put("Fill in the address");
        return;
    }
    istringstream iss{date.get_string()};
    iss >> dt;
    if (!iss)
    {
        status.set_label("Fill in the date correctly, e.g. 01.01.2001");
        redraw();
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
            status.set_label("Fill in purchases correctly (name | price | count), e.g. Minecraft | 19.18 | 1");
            redraw();
            return;
        }
    }
    if (vp.size() != 0)
        orders.push_back(Order{nm, addr, dt, vp});
    else
    {
        purchases.put("Fill in purchases");
        return;
    }
    clear_fields();
    orders_box.put(to_string(++orders_count));
    redraw();
}

void Orders_window::clear_fields()
{
    string s{""};
    name.put(s);
    address.put(s);
    date.put(s);
    purchases.put(s);
    status.set_label(s);
}

//------------------------------------------------------------------------------
