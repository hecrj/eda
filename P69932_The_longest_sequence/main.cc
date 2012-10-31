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
 * @param  it1 Current position in a
 * @param  b   A set of integers
 * @param  it2 Current position in b
 * @return     Size of the longest sequence from it1 to a.end() and
 *                  it2 to b.end()
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

/**
 * Given two sets obtains the size of the longest incresing
 * sequence interspersing the numbers of every set.
 * @param  a A set of integers
 * @param  b A set of integers
 * @return   Size of the longest increasint and interspersed sequence
 *                of a and b.
 */
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

/**
 * Given an input line of integers obtains two sets
 * classifying each integer in even or odd.
 * @param line Line of integers
 * @param even Set of even numbers
 * @param odd  Set of odd numbers
 */
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

/**
 * Reads lines of integers and obtains the size of the
 * longest increasing and interspersed sequence of even
 * and odd numbers.
 * @return Execution status
 */
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
