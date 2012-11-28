#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

typedef vector< vector<int> > Board;
typedef vector< vector<bool> > Visited;

struct Pos
{
	int i;
	int j;

	inline Pos(int i , int j)
	:	i(i),
		j(j)
	{	}
};

int stoi(const string &s)
{
	int r = 0;
	int l = s.length();

	for(int i = 0; i < l; ++i)
	{
		r = r*10 + (int)(s[i] - '0');
	}

	return r;
}

void read_board(Board &b, queue<Pos> &nodes)
{
	int n = b.size();
	int m = b[0].size();

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			string s;
			cin >> s;

			if(s == "X")
				b[i][j] = -1;
			else
			{
				b[i][j] = stoi(s);
				nodes.push(Pos(i, j));
			}
		}
	}
}

int connected_bishops(const Board &b, Pos u, Visited &v, int &size)
{
	int bishops = 0;
	size = 0;

	if(u.i < 0 or u.i >= b.size())
		return 0;

	if(u.j < 0 or u.j >= b[0].size())
		return 0;

	if(v[u.i][u.j] or b[u.i][u.j] < 0)
		return 0;

	bishops = b[u.i][u.j];
	size = 1;

	// Mark the node as visited
	v[u.i][u.j] = true;

	for(int i = -1; i <= 1; ++i)
	{
		if(i == 0)
			continue;

		for(int j = -1; j <= 1; ++j)
		{
			if(j == 0)
				continue;

			int rel_size;
			bishops += connected_bishops(b, Pos(u.i+i, u.j+j), v, rel_size);
			size += rel_size;
		}
	}

	return bishops;
}

bool are_connected_bishops_distributable_in(const Board &b, const Pos &u, Visited &v, int &n)
{
	int size;
	int bishops = connected_bishops(b, u, v, size);

	if(bishops % size != 0)
		return false;

	n = bishops / size;
	return true;
}

bool are_bishops_distributable_in(const Board &b, queue<Pos> &nodes)
{
	if(nodes.empty())
		return true;

	Visited v(b.size(), vector<bool>(b[0].size(), false));
	Pos u = nodes.front();
	nodes.pop();

	int ref_num_bishops;
	if(not are_connected_bishops_distributable_in(b, u, v, ref_num_bishops))
		return false;

	while(not nodes.empty())
	{
		Pos p = nodes.front();
		nodes.pop();

		if(v[p.i][p.j])
			continue;

		int num_bishops;
		if(not are_connected_bishops_distributable_in(b, p, v, num_bishops))
			return false;

		if(num_bishops != ref_num_bishops)
			return false;
	}

	return true;
}

int main()
{
	int t;
	cin >> t;

	for(int i = 0; i < t; ++i)
	{
		int n, m;
		cin >> n >> m;

		Board b(n, vector<int>(m));
		queue<Pos> nodes;
		read_board(b, nodes);

		cout << "Case " << i+1 << ": ";

		if(are_bishops_distributable_in(b, nodes))
			cout << "yes";
		else
			cout << "no";

		cout << endl;
	}

	return 0;
}
