#include <iostream>
#include <vector>

using namespace std;

/**
 * Tells whether x is in v between v[l..r].
 * @param  x Value to search
 * @param  v An 'almost' sorted vector
 * @param  l Position to start
 * @param  r Position to end
 * @return   True if x belongs to v, false otherwise
 */
bool resistant_search_i(double x, const vector<double> &v, int l, int r)
{
	if(l >= r)
		return false;

	int m = (r+l) / 2;
	
	if(x == v[m])
		return true;

	if(m-1 >= 0 and v[m-1] == x)
		return true;

	if(m+1 < v.size() and v[m+1] == x)
		return true;

	if(x < v[m])
		return resistant_search_i(x, v, l, m);
	
	return resistant_search_i(x, v, m+1, r);
}

/**
 * Tells whether x is in v.
 * @param  x [description]
 * @param  v An 'almost' sorted vector. By 'almost' sorted we understand
 *           a vector that can have at most a pair of indices i and j
 *           such that 0 <= i < j < v.size() and v[i] > v[j]
 * @return   True if x belongs to v, false otherwise
 */
bool resistant_search(double x, const vector<double> &v)
{
	return resistant_search_i(x, v, 0, v.size());
}

/**
 * For testing purposes only. Self-explanatory.
 * @return Execution status
 */
int main()
{
	cout << "Enter vector size: ";
	int n;
	cin >> n;

	cout << "Enter vector elements:" << endl;
	vector<double> v(n);
	
	for(int i = 0; i < n; ++i)
		cin >> v[i];

	cout << "Element to search: ";
	int x;
	cin >> x;

	cout << "Element " << (resistant_search(x, v) ? "found" : "not found") << endl;

	return 0;
}
