#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef vector< vector<char> > Map;

/**
 * Tells whether there is a treasure reachable in a map starting
 * in the (x, y) position.
 * @param  map     A treasure map!
 * @param  visited Set of visited coordinates
 * @param  x       X position coordinate
 * @param  y       Y position coordinate
 * @return         True if exists a map reachable starting from (x, y),
 *                      false otherwise
 */
bool is_reachable(const Map &map, set< pair<int, int> > &visited, int x, int y)
{
	if(x >= map[0].size() or y >= map.size())
		return false;

	pair<int, int> pos;
	pos.first = x;
	pos.second = y;

	if(visited.find(pos) != visited.end())
		return false;

	visited.insert(pos);

	if(map[y][x] == 't')
		return true;

	if(map[y][x] == 'X')
		return false;

	return (
		is_reachable(map, visited, x+1, y) or
		is_reachable(map, visited, x, y+1) or
		is_reachable(map, visited, x-1, y) or
		is_reachable(map, visited, x, y-1)
	);
}

/**
 * Reads a treasure map!
 * @param map An empty treasure map
 */
void read_map(Map &map)
{
	int n = map.size();
	int m = map[0].size();

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

	Map map(n, vector<char>(m));
	read_map(map);

	int r, c;
	cin >> r >> c;

	set< pair<int, int> > visited;
	cout << (is_reachable(map, visited, c-1, r-1) ? "yes" : "no") << endl;

	return 0;
}
