#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector< vector<char> > Map;
typedef vector< vector<bool> > Marks;
typedef pair<int, int> Node;

/**
 * Reads a treasure map!
 * @param map An empty treasure map
 * @param n Number of rows
 * @param m Number of columns
 */
void read_map(Map &map, int n, int m)
{
	map = Map(n, vector<char>(m));

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			cin >> map[i][j];
}

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
 * Gets the number of reachable treasures starting from the node n.
 * @param  map     A treasure map!
 * @param  visited Set of visited nodes
 * @param  n       Current node
 * @return         The number of reachable treasures starting from n.
 */
int get_treasures(const Map &map, Node n)
{
	int treasures = 0;
	
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
				treasures++;

			push_adjacent(map, pending, n, 1, 0);
			push_adjacent(map, pending, n, 0, 1);
			push_adjacent(map, pending, n, -1, 0);
			push_adjacent(map, pending, n, 0, -1);
		}
	}

	return treasures;
}

/**
 * Reads a treasure map and tells the number of treasures
 * reachable from an starting node.
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

	cout << get_treasures(map, make_pair(c-1, r-1)) << endl;

	return 0;
}
