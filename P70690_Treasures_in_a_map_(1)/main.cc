#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef vector< vector<char> > Map;
typedef pair<int, int> Node;

/**
 * Tells whether there is a treasure reachable in a map starting
 * from n node.
 * @param  map     A treasure map!
 * @param  visited Set of visited coordinates
 * @param  n       Current node
 * @return         True if exists a map reachable starting from n,
 *                      false otherwise
 */
bool is_reachable_i(const Map &map, set<Node> &visited, Node n)
{
	if(n.first < 0 or n.second < 0)
		return false;

	if(n.first >= map[0].size() or n.second >= map.size())
		return false;

	if(map[n.second][n.first] == 'X')
		return false;

	if(visited.find(n) != visited.end())
		return false;

	visited.insert(n);

	if(map[n.second][n.first] == 't')
		return true;

	return (
		is_reachable_i(map, visited, make_pair(n.first + 1, n.second)) or
		is_reachable_i(map, visited, make_pair(n.first, n.second + 1)) or
		is_reachable_i(map, visited, make_pair(n.first - 1, n.second)) or
		is_reachable_i(map, visited, make_pair(n.first, n.second - 1))
	);
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
	set<Node> visited;

	return is_reachable_i(map, visited, n);
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
