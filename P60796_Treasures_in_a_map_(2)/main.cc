#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

const int max_dist = numeric_limits<int>::max();

typedef vector< vector<char> > Map;
typedef pair<int, int> Node;
typedef vector< vector<int> > Distances;

/**
 * Map information: pending nodes and minimum distances.
 */
struct MapInfo
{
	queue<Node> pending;
	Distances min_dist;
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
	info.min_dist = Distances(n, vector<int>(m));

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
	
	if(v.first < 0 or v.first >= map[0].size())
		return;

	if(v.second < 0 or v.second >= map.size())
		return;

	if(map[v.second][v.first] != 'X')
	{
		int new_dist = 1 + info.min_dist[u.second][u.first];
		int min_dist_v = info.min_dist[v.second][v.first];

		if(new_dist < min_dist_v)
		{
			info.min_dist[v.second][v.first] = new_dist;

			info.pending.push(v);
		}
	}
}

/**
 * Calculates the shortest path to a treasure using the Dijkstra's
 * algorithm!
 * @param  map  A treasure map
 * @param  info Map info
 * @param  n    Source node
 * @param  t    Found treasure node
 * @return      True if a treasure is found, false otherwise
 */
bool calculate_path_dijkstra(const Map &map, MapInfo &info, Node n, Node &t)
{
	info.min_dist[n.second][n.first] = 0;
	info.pending.push(n);

	while(! info.pending.empty())
	{
		Node u = info.pending.front();
		info.pending.pop();

		if(map[u.second][u.first] == 't')
		{
			t = u;
			return true;
		}

		adjacent_update(map, info, u, 1, 0);
		adjacent_update(map, info, u, 0, 1);
		adjacent_update(map, info, u, -1, 0);
		adjacent_update(map, info, u, 0, -1);
	}

	return false;
}

/**
 * Calculates the minimum distance to a treasure in the map.
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
 * Reads a treasure map and tells the minimum distance to
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
		cout << "minimum distance: " << distance;

	else
		cout << "no treasure can be reached";

	cout << endl;
}
