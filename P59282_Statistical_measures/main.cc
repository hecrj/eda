#include <iostream>
#include <iomanip>
#include <string>
#include <queue>

using namespace std;

/**
 * Statistics class header.
 */
class Statistics
{

private:
	priority_queue< int, vector<int>, greater<int> > elements;
	int max;
	int sum;
	double mean;

public:
	Statistics();

	void push(int k);
	void pop();
	void print(int p);
};

/**
 * Statistics constructor.
 */
Statistics::Statistics()
{
	sum = 0;
}

/**
 * Adds an element to the current statistics.
 * @param k The element to add
 */
void Statistics::push(int k)
{
	if(elements.size() == 0)
		max = mean = k;

	else if(k > max)
		max = k;

	elements.push(k);
	sum += k;
	mean = double(sum) / double(elements.size());
}

/**
 * Deletes the smallest element in the current
 * statistics.
 */
void Statistics::pop()
{
	if(elements.size() > 0)
	{
		int k = elements.top();
		elements.pop();

		sum -= k;
		mean = double(sum) / double(elements.size());
	}
}

/**
 * Prints statistics data (minimum, maximum and mean) with
 * the desired precision.
 * @param p The desired precision
 */
void Statistics::print(int p)
{
	if(elements.size() == 0)
		cout << "no elements";

	else
	{
		cout << "minimum: " << elements.top() << ", ";
		cout << "maximum: " << max << ", ";
		cout << "average: " << fixed << setprecision(p) << mean;
	}

	cout << endl;
}

/**
 * Shows statistics based in the elements given by the input stream.
 * @return Execution status
 */
int main()
{
	Statistics stats;
	string cmd;

	while(cin >> cmd)
	{
		if(cmd == "delete")
			stats.pop();
		
		else if(cmd == "number")
		{
			int k;
			cin >> k;

			stats.push(k);
		}

		stats.print(4);
	}

	return 0;
}
