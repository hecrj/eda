#include <iostream>
#include <vector>

using namespace std;

/**
 * Reads a vector from the input stream in v.
 * @param v An empty initialized vector
 */
void read_vector(vector<int> &v)
{
	int n = v.size();

	for(int i = 0; i < n; ++i)
		cin >> v[i];
}

/**
 * Tells whether in d there are two diamonds that
 * sum v.
 * @param  d A vector of diamonds
 * @param  v Wedding diamond value
 * @return   True if there are two diamonds that sum v,
 *                false otherwise.
 */
bool married(vector<int> &d, int v)
{
	vector<bool> f(v);

	int n = d.size();

	for(int i = 0; i < n; ++i)
	{
		if(d[i] < v)
		{
			if(f[v-d[i]])
				return true;
			
			f[d[i]] = true;
		}
	}

	return false;
}

/**
 * Reads a vector of diamonds and a diamond value and tells
 * whether it is possible to obtain the diamond using two
 * diamonds in the vector.
 * @return Execution status
 */
int main()
{
	int v, n;

	cin >> v >> n;

	while(v != 0 and n != 0)
	{
		vector<int> d(n);
		read_vector(d);
		
		cout << (married(d, v) ? "married" : "single") << endl;

		cin >> v >> n;
	}

	return 0;
}
