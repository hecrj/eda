#include <iostream>
#include <stack>

using namespace std;

/**
 * Implements this code:
 * void print(int n) {
 *  	if(n > 0) {
 *  		cout << ' ' << n;
 *  		print(n-1);
 *  		print(n-1);
 *  	}
 * }
 * without using recursion.
 * @param n Original parameter
 */
void print(int n)
{
	cout << ' ' << n;

	stack<int> s;

	for(int i = 1; i < n; ++i)
	{
		stack<int> sc(s);
		stack<int> inv;

		while(! sc.empty())
		{
			inv.push(sc.top());
			sc.pop();
		}

		while(! inv.empty())
		{
			s.push(inv.top());
			inv.pop();
		}

		s.push(i);
	}

	stack<int> s2(s);

	while(!s.empty())
	{
		cout << ' ' << s.top();
		s.pop();
	}

	while(!s2.empty())
	{
		cout << ' ' << s2.top();
		s2.pop();
	}
}

/**
 * Original main of the statement.
 * @return Execution status
 */
int main() {
	int n;
	while(cin >> n) {
		print(n);
		cout << endl;
	}
}
