
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#pragma once

#include "GUI.h" // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"
#include "words.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Words_window : Graph_lib::Window
{
    Words_window(Point xy, int w, int h, const string& title)
        : Window(xy, w, h, title),
        fname_box{ Point{x_max() - 200, 50}, 130, 20, "First enter a file name and click \"Load file\" " },
        char_box{ Point{x_max() - 50, 80}, 20, 20, "" },
        n_box{ Point{x_max() - 20, 110}, 20, 20, "n=" },
        freq_box{ Point{x_max() - 100, 230}, 100, 20, "" },
        mobox{ Point{10,10}, 300, y_max() - 20, "" },
        load_button{ Point{x_max() - 70, 50}, 70, 20, "Load file", [](Address, Address pw)
              {
                  reference_to<Words_window>(pw).load_file();
              } },
        flwords_button{ Point{x_max() - 300, 80}, 250, 20, "Show all words starting with a letter:", [](Address, Address pw)
              {
                  reference_to<Words_window>(pw).show_flwords();
              } },
        lcwords_button{ Point{x_max() - 300, 110}, 250, 20, "Show all words with n letters", [](Address, Address pw)
              {
                  reference_to<Words_window>(pw).show_lcwords();
              } },
        long_button{ Point{x_max() - 300, 140}, 250, 20, "Show the longest word in the file", [](Address, Address pw)
              {
                  reference_to<Words_window>(pw).show_longest_word();
              } },
        short_button{ Point{x_max() - 300, 170}, 250, 20, "Show the shortest word in the file", [](Address, Address pw)
              {
                  reference_to<Words_window>(pw).show_shortest_word();
              } },
        mfreq_button{ Point{x_max() - 300, 200}, 300, 20, "Show the most frequently occurring word", [](Address, Address pw)
              {
                  reference_to<Words_window>(pw).show_mfreq_word();
              } },
        frequency_button{ Point{x_max() - 300, 230}, 200, 20, "Show frequency of a word:", [](Address, Address pw)
              {
                  reference_to<Words_window>(pw).show_frequency();
              } },
        quit_button{Point{x_max() - 70, 0}, 70, 20, "Exit", [](Address, Address pw)
                      {
                          reference_to<Words_window>(pw).quit();
					  } },
        status{ Point{x_max() - 450, 40}, ""}
	{
        fill_shorts(shorts);
        attach(flwords_button);
        attach(lcwords_button);
        attach(load_button);
        attach(long_button);
        attach(short_button);
        attach(mfreq_button);
        attach(frequency_button);
        attach(mobox);
        attach(fname_box);
        attach(char_box);
        attach(n_box);
        attach(freq_box);
        attach(quit_button);
        attach(status);
        status.set_color(Color::red);
    }

private:

    map<string, string> shorts;
    map<string, int> ms;
    string filename;

    In_box fname_box, char_box, n_box, freq_box;
    Multiline_out_box mobox;
    Button load_button, flwords_button, lcwords_button, long_button, 
           short_button, mfreq_button, frequency_button, quit_button;
    Text status;

    void quit() { Window::hide(); }
    void load_file();
    void show_flwords();
    void show_lcwords();
    void show_longest_word();
    void show_shortest_word();
    void show_mfreq_word();
    void show_frequency();
    void fill_map(fstream&);
};

//------------------------------------------------------------------------------
