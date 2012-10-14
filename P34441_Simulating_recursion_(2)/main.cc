#include <iostream>
#include <stack>

using namespace std;

/**
 * Implements this code:
 * void print(int n) {
 *  	if(n > 0) {
 *  		print(n-1);
 *  		cout << ' ' << n;
 *  		print(n-1);
 *  	}
 * }
 * without using recursion.
 * @param n Original parameter
 */
void print(int n)
{
	stack<int> s;

	for(int i = 1; i <= n; ++i)
	{
		stack<int> sc(s);
		
		s.push(i);

		while(! sc.empty())
		{
			s.push(sc.top());
			sc.pop();
		}
	}

	while(! s.empty())
	{
		cout << ' ' << s.top();
		s.pop();
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
