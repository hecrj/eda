#include <iostream>
#include <list>

using namespace std;

void print(list<int> &l)
{
	list<int>::iterator it = l.begin();

	while(it != l.end())
	{
		if(it != l.begin())
			cout << ' ';

		cout << *it;
		it++;
	}

	cout << endl;
}

void zeros_and_ones(list<int> &conf, int n)
{
	if(conf.size() == n)
		print(conf);
	else
	{
		conf.push_back(0);
		zeros_and_ones(conf, n);
		conf.pop_back();

		conf.push_back(1);
		zeros_and_ones(conf, n);
		conf.pop_back();
	}
}

int main()
{
	int n;
	cin >> n;

	list<int> conf;
	zeros_and_ones(conf, n);
}
