#pragma once

// From main.cpp - chapter 21, exercise 14

#include "punct_stream.h"
#include <map>
#include <set>

void fill_shorts(map<string, string>& shorts);
string get_first_word(string& word, int n);
void unshorten(map<string, int>& ms, string& word, const map<string, string>& shorts);
void remove_plurals(map<string, int>& ms);

int word_frequency(const map<string, int>& ms, const string& word);
string most_freq_word(const map<string, int>& ms);
string the_longest_word(const map<string, int>& ms);
string the_shortest_word(const map<string, int>& ms);
set<string> get_flwords(const map<string, int>& ms, char ch);
set<string> get_lcwords(const map<string, int>& ms, int letter_count);
template<typename T>
void print_set(const set<T>& st);