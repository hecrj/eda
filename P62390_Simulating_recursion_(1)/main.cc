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
	stack<int> s;
	s.push(n);

	int c;
	while(not s.empty())
	{
		c = s.top();
		s.pop();

		cout << ' ' << c;

		if(c > 1)
		{
			s.push(c-1);
			s.push(c-1);
		}
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
