// Chapter 21, exercise 13: clean up a text file - replace punctuations with whitespaces;
// put words into lower case; replace "don't" with "do not" etc.;
// remove plurals (for all words where you find "word" and "words")

#include "punct_stream.h"
#include <map>

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

	for (const auto& s : ms)
			cout << s.first << ": " << s.second << endl;
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
