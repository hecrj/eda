#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

typedef set<int>::const_iterator Iterator;

/**
 * Given two sets obtains the size of the longest incresing
 * sequence interspersing the numbers of every set.
 * @param  a   A set of integers
 * @param  it1 Current position of a
 * @param  b   A set of integers
 * @param  it2 [description]
 * @return     [description]
 */
int get_size_longest_sequence_i(const set<int> &a, Iterator &it1,
	const set<int> &b, Iterator &it2)
{
	while(it1 != a.end() and *it1 < *it2)
		it1++;

	if(it1 == a.end())
		return 2;

	return 1 + get_size_longest_sequence_i(b, it2, a, it1);
}

int get_size_longest_sequence(const set<int> &a, const set<int> &b)
{
	Iterator it1 = a.begin();
	Iterator it2 = b.begin();

	if(it1 == a.end() and it2 == b.end())
		return 0;

	if(it1 == a.end() or it2 == b.end())
		return 1;

	if(*it1 < *it2)
		return get_size_longest_sequence_i(a, it1, b, it2);
	else
		return get_size_longest_sequence_i(b, it2, a, it1);
}

void read_sequence(const string &line, set<int> &even, set<int> &odd)
{
	stringstream stream(line);
	int n;

	while(stream >> n)
	{
		if(n % 2 == 0) even.insert(n);
		else odd.insert(n);
	}
}

int main()
{
	string line;

	while(! getline(cin, line).eof())
	{
		set<int> even;
		set<int> odd;
		
		read_sequence(line, even, odd);

		cout << get_size_longest_sequence(even, odd) << endl;
	}

	return 0;
}
