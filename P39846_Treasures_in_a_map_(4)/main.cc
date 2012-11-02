#include <iostream>
#include <limits>
#include <vector>
#include <set>

using namespace std;

const int max_dist = numeric_limits<int>::max();

typedef pair<int, int> Node;
typedef vector< vector<char> > Map;
typedef set< pair<int, Node> > Nodes;
typedef vector< vector<int> > Dist;

/**
 * Map information: set of nodes and minimum distances.
 */
struct MapInfo
{
	Nodes nodes;
	Dist min_dist;
};

/**
 * Reads a treasure map!
 * @param map An empty treasure map
 * @param info MapInfo about the map
 * @param n Number of rows
 * @param m Number of columns
 */
void read_map(Map &map, MapInfo &info, int n, int m)
{
	map = Map(n, vector<char>(m));
	info.min_dist = Dist(n, vector<int>(m));

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			cin >> map[i][j];
						
			info.min_dist[i][j] = max_dist;
		}
	}
}

/**
 * Gets the number of reachable treasures starting from the node n.
 * @param  map     A treasure map!
 * @param  visited Set of visited nodes
 * @param  n       Current node
 * @return         The number of reachable treasures starting from n.
 */
int get_treasures_i(const Map &map, set<Node> &visited, Node n)
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
		get_treasures_i(map, visited, make_pair(n.first + 1, n.second)) +
		get_treasures_i(map, visited, make_pair(n.first, n.second + 1)) +
		get_treasures_i(map, visited, make_pair(n.first - 1, n.second)) +
		get_treasures_i(map, visited, make_pair(n.first, n.second - 1))
	);

	if(map[n.second][n.first] == 't')
		return 1 + treasures;

	return treasures;
}

/**
 * Gets the number of reachable treasures in the map starting from n.
 * @param  map A treasure map
 * @param  n   The starting node
 * @return     The number of reachable treasures
 */
int get_treasures(const Map &map, Node n)
{
	set<Node> visited;

	return get_treasures_i(map, visited, n);
}

/**
 * Updates an adjacent node to u given a map, its info and
 * the relative position of the adjacent node (i, j)
 * @param map  A treasure map
 * @param info Map info
 * @param u    Current node
 * @param i    Relative x coordinate
 * @param j    Relative y coordinate
 */
void adjacent_update(const Map &map, MapInfo &info, Node u, int i, int j)
{
	Node v = make_pair(u.first + i, u.second + j);
	
	if(v.first < 0 or v.first >= map[0].size() or
		v.second < 0 or v.second >= map.size())
		return;

	if(map[v.second][v.first] != 'X')
	{
		int dist = 1 + info.min_dist[u.second][u.first];

		int min_dist_v = info.min_dist[v.second][v.first];

		if(dist < min_dist_v)
		{
			info.nodes.erase(make_pair(min_dist_v, v));

			info.min_dist[v.second][v.first] = dist;

			info.nodes.insert(make_pair(dist, v));
		}
	}
}

/**
 * Calculates the maximum distance to a treasure using the Dijkstra's
 * algorithm!
 * @param  map  A treasure map
 * @param  info Map info
 * @param  n    Source node
 * @param  t    Found treasure node
 * @return      True if a treasure is found, false otherwise
 */
bool calculate_path_dijkstra(const Map &map, MapInfo &info, Node n, Node &t)
{
	int treasures = get_treasures(map, n);
	bool found = (treasures > 0);

	info.min_dist[n.second][n.first] = 0;
	info.nodes.insert(make_pair(0, n));

	while(treasures > 0 and !info.nodes.empty())
	{
		Node u = info.nodes.begin()->second;
		info.nodes.erase(info.nodes.begin());

		if(map[u.second][u.first] == 't')
		{
			t = u;
			treasures--;
		}

		adjacent_update(map, info, u, 1, 0);
		adjacent_update(map, info, u, 0, 1);
		adjacent_update(map, info, u, -1, 0);
		adjacent_update(map, info, u, 0, -1);
	}

	return found;
}

/**
 * Calculates the maximum distance to a treasure in the map.
 * @param  map  A map
 * @param  info Map info
 * @param  n    Source node
 * @param  d    Distance to the treasure found
 * @return      True if a treasure is found, false otherwise
 */
bool calculate_path(const Map &map, MapInfo &info, Node n, int &d)
{
	Node t;

	d = 0;
	
	if(calculate_path_dijkstra(map, info, n, t))
	{
		d = info.min_dist[t.second][t.first];

		return true;
	}

	return false;
}

/**
 * Reads a treasure map and tells the maximum distance to
 * a treasure in the map.
 * @return Execution status
 */
int main()
{
	int n, m;
	cin >> n >> m;

	Map map;
	MapInfo info;

	read_map(map, info, n, m);

	Node node;
	cin >> node.second >> node.first;

	node.first--;
	node.second--;

	int distance;

	if(calculate_path(map, info, node, distance))
		cout << "maximum distance: " << distance;

	else
		cout << "no treasure can be reached";

	cout << endl;
}
