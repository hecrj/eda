#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef vector< vector<char> > Map;
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
 * Gets the number of reachable treasures starting from the node n.
 * @param  map     A treasure map!
 * @param  visited Set of visited nodes
 * @param  n       Current node
 * @return         The number of reachable treasures starting from n.
 */
int get_treasures(const Map &map, set<Node> &visited, Node n)
{
	if(n.first < 0 or n.second < 0)
		return 0;

	if(n.first >= map[0].size() or n.second >= map.size())
		return 0;

	if(map[n.second][n.first] == 'X')
		return 0;

	if(visited.find(n) != visited.end())
		return 0;

	visited.insert(n);

	int treasures = (
		get_treasures(map, visited, make_pair(n.first + 1, n.second)) +
		get_treasures(map, visited, make_pair(n.first, n.second + 1)) +
		get_treasures(map, visited, make_pair(n.first - 1, n.second)) +
		get_treasures(map, visited, make_pair(n.first, n.second - 1))
	);

	if(map[n.second][n.first] == 't')
		return 1 + treasures;

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

	Node node;
	cin >> node.second >> node.first;

	node.first--;
	node.second--;

	set<Node> visited;

	cout << get_treasures(map, visited, node) << endl;
}
