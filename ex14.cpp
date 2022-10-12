// Chapter 21, exercise 14: using the output from exercise 13, write a program
// to answer questions such as "How many occurrences of 'ship' are there in a
// file?" "Which word occurs most frequently?" "Which is the longest word?"
// "Which is the shortest?" "List all words starting with 's'." "List all four-
// letter words."

#include "punct_stream.h"
#include <map>
#include <set>

void fill_shorts(map<string,string>& shorts)
{
	shorts.insert(make_pair("n't", "not"));
	shorts.insert(make_pair("'ll", "will"));
	shorts.insert(make_pair("'ve", "have"));
	shorts.insert(make_pair("'re", "are"));
	shorts.insert(make_pair("'m", "am"));
}

string get_first_word(string& word, int n)
{
	string str = word;
	if (word == "won't")
		str = "will";
	else if (word == "can't")
		str = "can";
	else if (*(word.end() - 1) == '\'')
		str = { word.begin(), word.end() - 1 };
	else if ((*(word.end() - 2) == '\'') && (*(word.end() - 1) == 'd' || *(word.end() - 1) == 's'))	//we don't know exactly whether "had" or "would" (also "is" or "has")
		str = { word.begin(), word.end() - 2 };
	else if (n >= 0)
		str = { word.begin(), word.end() - n };
	return str;
}

void unshorten(map<string, int>& ms, string &word, const map<string, string>& shorts)
{
	int n = -1;
	for (const auto& sh : shorts)
		if (find_end(word.begin(), word.end(), sh.first.begin(), sh.first.end()) != word.end())
		{
			n = sh.first.size();
			++ms[sh.second];
			break;
		}
	++ms[get_first_word(word, n)];
}

void remove_plurals(map<string, int>& ms) 
{
	for (auto p = ms.begin(); p != ms.end();)
	{
		if ((*p).first.size() > 2 && (*p).first.back() == 's')
		{
			string singular{ (*p).first.begin(), (*p).first.end() - 1 };
			if (ms.find(singular) != ms.end())
			{
				ms[singular] += ms[(*p).first];
				p = ms.erase(p);
				continue;
			}
		}
		++p;
	}
}

//---------------------------------------------------------------------------------------------------------------

int count_of_word(const map<string, int>& ms, const string& word)
{
	auto p = ms.find(word);
	return p != ms.end() ? (*p).second : 0;
}

//---------------------------------------------------------------------------------------------------------------

string most_freq_word(const map<string, int>& ms)
{
	pair<string, int> mfw{"", 0};
	for (const auto& p : ms)
		if (p.second > mfw.second)
			mfw = p;
	return mfw.first;
}

//---------------------------------------------------------------------------------------------------------------

string the_longest_word(const map<string, int>& ms)
{
	string tlw{""};
	int sz = 0;
	for (const auto& p : ms)
		if (p.first.size() > sz)
		{
			tlw = p.first;
			sz = p.first.size();
		}
	return tlw;
}

//---------------------------------------------------------------------------------------------------------------

string the_shortest_word(const map<string, int>& ms)
{
	string tsw{ "" };
	int sz = INT16_MAX;
	for (const auto& p : ms)
		if (p.first.size() < sz)
		{
			tsw = p.first;
			sz = p.first.size();
		}
	return tsw;
}

//---------------------------------------------------------------------------------------------------------------

set<string> get_flwords(const map<string, int>& ms, char ch) 
{ //Words that start with the letter ch
	set<string> ss;
	for (const auto& p : ms)
		if (p.first.front() == ch)
			ss.insert(p.first);
	return ss;
}

//---------------------------------------------------------------------------------------------------------------

set<string> get_lcwords(const map<string, int>& ms, int letter_count)
{ //All the words that consist of letter_count 
	set<string> ss;
	for (const auto& p : ms)
		if (p.first.size() == letter_count)
			ss.insert(p.first);
	return ss;
}

//---------------------------------------------------------------------------------------------------------------

template<typename T>
void print_set(const set<T>& st)
{
	if (!st.empty())
		for (const auto& p : st)
			cout << p << endl;
}

//---------------------------------------------------------------------------------------------------------------

int main()
try
{
	ifstream ifs{ "ex13.txt" };
	if (!ifs)
		error("unable to open input file");
	Punct_stream ps{ ifs };

	ps.whitespace(";:,.?!()\"{}[]<>/&$@%^*|~-_");

	ps.case_sensitive(false);

	map<string, string> shorts;
	fill_shorts(shorts);

	map<string, int> ms;
	for (string word; ps >> word;)
	{
		if (find(word.begin(), word.end(), '\'') != word.end())
			unshorten(ms, word, shorts);
		else
			++ms[word]; 
	}

	remove_plurals(ms);

	//for (const auto& s : ms)
		//cout << s.first << ": " << s.second << endl;
	string w{"all"};
	cout << "Count of a word \"" << w << "\": " << count_of_word(ms, w) << endl;
	cout << "The longest word: " << most_freq_word(ms) << endl;
	cout << "The shortest word: " << the_shortest_word(ms) << endl;
	char ch = 's';
	set<string> ss{ get_flwords(ms,ch) };
	cout << "Words that start with the letter \'" << ch << "\':\n";
	print_set(ss);
	int n = 4;
	cout << endl << n << "-letter words:\n";
	set<string> ss2{ get_lcwords(ms,n) };
	print_set(ss2);
}
catch (Range_error& re)
{
	cerr << "Bad index: " << re.index << "\n";
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
