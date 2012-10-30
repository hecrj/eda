#include <iostream>
#include <string>
#include <map>

using namespace std;

/**
 * Iterator shortcut.
 */
typedef map<string, int>::const_iterator Iterator;

/**
 * Bag class header.
 */
class Bag
{

private:
	map<string, int> words;

	bool is_in(const string &word);
	void print_info(const string &name);

public:
	Bag();

	void store(const string &word);
	void remove(const string &word);
	void print_min();
	void print_max();

};

/**
 * Bag constructor.
 */
Bag::Bag()
{

}

/**
 * Tells whether a word is in the bag or not.
 * @param  word The word to find
 * @return      True if the word is already in the bag,
 *              false otherwise.
 */
bool Bag::is_in(const string &word)
{
	return (words.find(word) != words.end());
}

/**
 * Stores a word in the bag.
 * @param word The word to store.
 */
void Bag::store(const string &word)
{
	if(is_in(word))
		words[word] += 1;
	else
		words[word] = 1;
}

/**
 * Removes a word from the bag.
 * @param word The word to remove.
 */
void Bag::remove(const string &word)
{
	if(is_in(word))
	{
		words[word] -= 1;

		if(words[word] == 0)
			words.erase(word);
	}
}

/**
 * Prints info about the bag.
 * @param name The type of info to print (minimum or maximum).
 */
void Bag::print_info(const string &name)
{
	if(words.empty())
		cout << "indefinite " << name;

	else
	{
		Iterator it;

		if(name == "maximum")
		{
			it = words.end();
			it--;
		}
		else
			it = words.begin();

		cout << name << ": " << it->first << ", " << it->second << " time(s)";
	}

	cout << endl;
}

/**
 * Prints info about the minimum word (lexicographically).
 */
void Bag::print_min()
{
	print_info("minimum");
}

/**
 * Prints info about the maximum word (lexicographically).
 */
void Bag::print_max()
{
	print_info("maximum");
}

/**
 * Manages a Bag of Words!
 * @return Execution status
 */
int main()
{
	Bag bag;

	string action;

	while(cin >> action)
	{
		if(action == "store" or action == "delete")
		{
			string x;
			cin >> x;

			if(action == "store") bag.store(x);
			else bag.remove(x);
		}

		else if(action == "minimum?")
			bag.print_min();

		else
			bag.print_max();
	}

	return 0;
}
