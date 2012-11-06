#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector< vector<char> > Map;
typedef vector< vector<bool> > Marks;
typedef pair<int, int> Node;

/**
 * Adds an adjacent node to the pending nodes of a map given
 * the relative position of the adjacent node (i, j)
 * @param map  A treasure map
 * @param pending queue<Node> nodes
 * @param n    Current node
 * @param i    Relative x coordinate
 * @param j    Relative y coordinate
 */
void push_adjacent(const Map &map, queue<Node> &pending, Node n, int i, int j)
{
	Node v = make_pair(n.first + i, n.second + j);
	
	if(v.first < 0 or v.first >= map[0].size())
		return;

	if(v.second < 0 or v.second >= map.size())
		return;

	if(map[v.second][v.first] != 'X')
		pending.push(v);
}

/**
 * Tells whether there is a treasure reachable in the map starting
 * from n.
 * @param  map A treasure map
 * @param  n   The starting node
 * @return     True if there is any treasure reachable
 */
bool is_reachable(const Map &map, Node n)
{
	Marks visited(map.size(), vector<bool>(map[0].size(), false));
	queue<Node> pending;
	pending.push(n);

	while(not pending.empty())
	{
		Node n = pending.front();
		pending.pop();

		if(not visited[n.second][n.first])
		{
			visited[n.second][n.first] = true;

			if(map[n.second][n.first] == 't')
				return true;

			push_adjacent(map, pending, n, 1, 0);
			push_adjacent(map, pending, n, 0, 1);
			push_adjacent(map, pending, n, -1, 0);
			push_adjacent(map, pending, n, 0, -1);
		}
	}

	return false;
}

/**
 * Reads a treasure map!
 * @param map An empty treasure map
 */
void read_map(Map &map, int n, int m)
{
	map = Map(n, vector<char>(m));

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			cin >> map[i][j];
}

/**
 * Reads a treasure map and, given a position, tells
 * whether there is a reachable treasure!
 * @return Execution status
 */
int main()
{
	int n, m;
	cin >> n >> m;

	Map map;
	read_map(map, n, m);

	int r, c;
	cin >> r >> c;

	cout << (is_reachable(map, make_pair(c-1, r-1)) ? "yes" : "no") << endl;

	return 0;
}
