#include "words.h"

void fill_shorts(map<string, string>& shorts)
{
	shorts.insert(make_pair("n't", "not"));
	shorts.insert(make_pair("'ll", "will"));
	shorts.insert(make_pair("'ve", "have"));
	shorts.insert(make_pair("'re", "are"));
	shorts.insert(make_pair("'m", "am"));
}

//---------------------------------------------------------------------------------------------------------------

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

//---------------------------------------------------------------------------------------------------------------

void unshorten(map<string, int>& ms, string& word, const map<string, string>& shorts)
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

//---------------------------------------------------------------------------------------------------------------

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

int word_frequency(const map<string, int>& ms, const string& word)
{
	auto p = ms.find(word);
	return p != ms.end() ? (*p).second : 0;
}

//---------------------------------------------------------------------------------------------------------------

string most_freq_word(const map<string, int>& ms)
{
	pair<string, int> mfw{ "", 0 };
	for (const auto& p : ms)
		if (p.second > mfw.second)
			mfw = p;
	return mfw.first;
}

//---------------------------------------------------------------------------------------------------------------

string the_longest_word(const map<string, int>& ms)
{
	string tlw{ "" };
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

