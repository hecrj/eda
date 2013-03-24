#include <iostream>
#include <list>

using namespace std;

void print(list<bool> &l, int n, bool one)
{
	list<bool>::iterator it = l.begin();

	int i = 0;
	while(it != l.end())
	{
		if(i != 0)
			cout << ' ';

		cout << (*it ? '1' : '0');

		i++;
		it++;
	}

	while(i < n)
	{
		if(i != 0)
			cout << ' ';

		cout << (one ? '1' : '0');
		++i;
	}

	cout << endl;
}

void zeros_and_ones(list<bool> &conf, int n, int u, int ones)
{
	if(ones == u)
		print(conf, n, false);

	else if(conf.size() - ones == n - u)
		print(conf, n, true);

	else
	{
		conf.push_back(0);
		zeros_and_ones(conf, n, u, ones);
		conf.pop_back();

		conf.push_back(1);
		zeros_and_ones(conf, n, u, ones+1);
		conf.pop_back();
	}
}

int main()
{
	int n, u;
	cin >> n >> u;

	list<bool> conf;
	zeros_and_ones(conf, n, u, 0);
}
