#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int max_dist = numeric_limits<int>::max();

/**
 * Represents a Rock of the problem.
 */
struct Rock
{
	double x;
	double y;
	double r;
};

/**
 * Returns the absolute value of x.
 * @param  x A double
 * @return   |x|
 */
double my_abs(double x)
{
	if(x < 0) return -x;
	else return x;
}

/**
 * Reads a sequence of n rocks.
 * @param rocks An empty vector of size n
 * @param n     Number of rocks to read
 */
void read_rocks(vector<Rock> &rocks, int n)
{
	for(int i = 0; i < n; ++i)
		cin >> rocks[i].x >> rocks[i].y >> rocks[i].r;
}

/**
 * Pushes the adjacents rocks in the queue if they are reachable from
 * the current rock c.
 * @param rocks   The rocks in the river
 * @param d       Jump max distance
 * @param c       Current rock
 * @param pending Pending rocks queue (to visit)
 * @param dist    The number of minimum jumps to go to each rock
 */
void push_adjacents(const vector<Rock> &rocks, double d, int c,
	queue<int> &pending, vector<int> &dist)
{
	int n = rocks.size();
	
	for(int i = 1; i < n; ++i)
	{
		double c1 = my_abs(rocks[c].x - rocks[i].x);
		double c2 = my_abs(rocks[c].y - rocks[i].y);
		double h = sqrt(c1*c1 + c2*c2);

		if(d >= (h - rocks[c].r - rocks[i].r))
		{
			int new_dist = dist[c] + 1;

			if(new_dist < dist[i])
			{
				dist[i] = dist[c] + 1;
				pending.push(i);
			}
		}
	}
}

/**
 * Returns the minimum number of jumps to go from the first rock
 * to the last one in the river.
 * @param  rocks Rocks in the river
 * @param  d     Jump max distance
 * @return       The min number of jumps
 */
int get_number_jumps(const vector<Rock> &rocks, double d)
{
	vector<int> dist(rocks.size(), max_dist);
	queue<int> pending;

	dist[0] = 0;
	pending.push(0);

	while(not pending.empty())
	{
		int c = pending.front();
		pending.pop();

		if(c == rocks.size()-1)
			return dist[c];

		push_adjacents(rocks, d, c, pending, dist);
	}

	return 0;
}

/**
 * Reads sequences of rocks and for each one tells the minimum number
 * of jumps to win The Lake of the Dragon God.
 * @return Execution status
 */
int main()
{
	int n;
	double d;

	while(cin >> n >> d)
	{
		vector<Rock> rocks(n);
		read_rocks(rocks, n);

		int jumps = get_number_jumps(rocks, d);

		if(jumps == 0) cout << "Xof!";
		else cout << jumps;

		cout << endl;
	}

	return 0;
}
