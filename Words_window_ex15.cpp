#include "Words_window_ex15.h"


void Words_window::load_file()
{
    ms.clear();
    status.set_label("");
    filename = fname_box.get_string();
    fstream ifs{ filename };
    if (!ifs)
        status.set_label("Unable to open input file " + filename);
    else
    {
        fill_map(ifs);
        if (ms.empty())
            status.set_label("Empty word database in the file " + filename);
        else
            status.set_label(filename + " loaded successfully");
    }
    redraw();
}

//------------------------------------------------------------------------------

void Words_window::fill_map(fstream& ifs)
{
    Punct_stream ps{ ifs };
    ps.whitespace(";:,.?!()\"{}[]<>/&$@%^*|~-_");
    ps.case_sensitive(false);

    for (string word; ps >> word;)
    {
        if (std::find(word.begin(), word.end(), '\'') != word.end())
            unshorten(ms, word, shorts);
        else
            ++ms[word];
    }
    remove_plurals(ms);
}

//------------------------------------------------------------------------------

void Words_window::show_flwords()
{
    status.set_label("");
    string s = char_box.get_string();
    if (s.empty() || s.size() > 1)
        status.set_label("Enter just one letter!");
    else
    {
        set<string> ss{ get_flwords(ms, s.front()) };
        ostringstream oss;
        for (const auto& p : ss)
            oss << p << endl;
        mobox.put(oss.str());
    }
    redraw();
}

//------------------------------------------------------------------------------

void Words_window::show_lcwords()
{
    status.set_label("");
    int n = n_box.get_int();
    if (n <= 0)
        status.set_label("Enter positive number!");
    else
    {
        set<string> ss{ get_lcwords(ms, n) };
        ostringstream oss;
        for (const auto& p : ss)
            oss << p << endl;
        mobox.put(oss.str());
    }
    redraw();
}

//------------------------------------------------------------------------------

void Words_window::show_longest_word()
{
    status.set_label("");
    mobox.put(the_longest_word(ms));
    redraw();
}

//------------------------------------------------------------------------------

void Words_window::show_shortest_word()
{
    status.set_label("");
    mobox.put(the_shortest_word(ms));
    redraw();
}

//------------------------------------------------------------------------------

void Words_window::show_mfreq_word()
{
    status.set_label("");
    mobox.put(most_freq_word(ms));
    redraw();
}

//------------------------------------------------------------------------------

void Words_window::show_frequency()
{
    status.set_label("");
    string word{ freq_box.get_string() };
    int n = 0;
    if (word.empty())
        status.set_label("Enter a word!");
    else
    {
        n = word_frequency(ms, word);
        mobox.put(word + ": " + to_string(n));
    }
    redraw();
}