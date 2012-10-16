#include <iostream>
#include <string>
#include <map>

using namespace std;

/**
 * Casino class header.
 */
class Casino
{

private:
	map<string, int> players;

	void already_in(const string &player);
	void not_in(const string &player);

public:
	Casino();

	bool is_in(const string &player);
	void enters(const string &player);
	void leaves(const string &player);
	void wins(const string &player, int amount);
	void show_info();
};

/**
 * Creates a new Casino!
 */
Casino::Casino()
{

}

/**
 * Prints a message saying that player is already in the casino.
 * @param player Name of the player
 */
void Casino::already_in(const string &player)
{
	cout << player << " is already in the casino" << endl;
}

/**
 * Prints a message saying that player is not in the casino.
 * @param player Name of the player
 */
void Casino::not_in(const string &player)
{
	cout << player << " is not in the casino" << endl;
}

/**
 * Tells whether a player is already in the casino or not.
 * @param  player The name of the player
 * @return        True if player is in the casino, false otherwise
 */
bool Casino::is_in(const string &player)
{
	return (players.find(player) != players.end());
}

/**
 * Adds a player in the casino.
 * @param player The name of the player
 */
void Casino::enters(const string &player)
{
	if(is_in(player)) already_in(player);
	else players[player] = 0;
}

/**
 * Removes a player from the casino.
 * @param player [description]
 */
void Casino::leaves(const string &player)
{
	if(is_in(player))
	{
		cout << player << " has won " << players[player] << endl;
		players.erase(player);
	}

	else not_in(player);
}

/**
 * Adds some amount to a registered player in the casino.
 * @param player Name of the player
 * @param amount Amount to add
 */
void Casino::wins(const string &player, int amount)
{
	if(is_in(player))
	{
		players[player] += amount;
	}

	else not_in(player);
}

/**
 * Shows information about the current registered players in
 * the casino.
 */
void Casino::show_info()
{
	for(int i = 0; i < 10; ++i)
		cout << '-';
		
	cout << endl;

	map<string, int>::iterator it = players.begin();

	while(it != players.end())
	{
		cout << it->first << " is winning " << it->second << endl;
		++it;
	}
}

/**
 * Manages a casino!
 * @return Execution status
 */
int main()
{
	Casino casino;
	string player, action;

	while(cin >> player >> action)
	{
		if(action == "enters")
			casino.enters(player);

		else if(action == "leaves")
			casino.leaves(player);

		else if(action == "wins")
		{
			int amount;
			cin >> amount;

			casino.wins(player, amount);
		}
	}

	casino.show_info();

	return 0;
}
