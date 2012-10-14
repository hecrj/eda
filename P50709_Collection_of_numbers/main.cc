#include <iostream>
#include <queue>

using namespace std;

/**
 * Reads an integer from the input stream.
 * @return The integer read.
 */
int readint()
{
	int k;
	cin >> k;

	return k;
}

/**
 * Manages a collection of integers:
 * S x	:	Store x
 * A	:	Print max
 * R	:	Remove max
 * I x	:	Increment max by x
 * D x	:	Decrement max by x
 * @return Execution status
 */
int main()
{
	priority_queue<int> col;

	char c;

	while(cin >> c)
	{
		switch(c)
		{
			case 'S':
				col.push(readint());
				break;

			case 'A':
				if(col.empty()) cout << "error!";
				else cout << col.top();
				
				cout << endl;
				break;

			case 'R':
				if(col.empty()) cout << "error!" << endl;
				else col.pop();

				break;

			case 'I':
			case 'D':
			{
				int x = readint();

				if(col.empty()) cout << "error!" << endl;
				else
				{
					int k = col.top();
					col.pop();

					if(c == 'I') col.push(k+x);
					else col.push(k-x);
				}
			}

			default:
				break;
		}
	}
}
