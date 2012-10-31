#include <iostream>
#include <set>

using namespace std;

/**
 * Iterator shortcut.
 */
typedef multiset<int>::iterator Iterator;

/**
 * Bag class header.
 */
class Bag
{

private:
	multiset<int> jewels;
	int size;
	long long int amount;

	bool is_full() const;

public:
	Bag(int size);

	long long int get_amount() const;

	void leave(int jewel, multiset<int> &cave);
	void take(int jewel, multiset<int> &cave);
};

/**
 * Bag constructor.
 * @param size The maximum size of the bag.
 */
Bag::Bag(int size)
{
	this->size = size;
	amount = 0;
}

/**
 * Tells whether the bag is full or not.
 * @return True if the bag is full, false otherwise.
 */
bool Bag::is_full() const
{
	return jewels.size() >= size;
}

/**
 * Returns the total amount of the jewels in the bag.
 * @return The total amount of the jewels in the bag.
 */
long long int Bag::get_amount() const
{
	return amount;
}

/**
 * Leaves a jewel in the cave. But if the jewel is
 * valuable enough then its left in the bag.
 * @param jewel Jewel value
 * @param cave  Set of jewels in the cave
 */
void Bag::leave(int jewel, multiset<int> &cave)
{
	if(is_full())
	{
		if(jewel > *(jewels.begin()))
		{
			Iterator it = jewels.begin();

			amount = amount - (*it) + jewel;

			cave.insert(*it);
			jewels.erase(it);

			jewels.insert(jewel);
		}
		else
			cave.insert(jewel);
	}

	else
	{
		jewels.insert(jewel);
		amount += jewel;
	}
}

/**
 * Takes a jewel from the cave or the bag,
 * if not found in the cave.
 * @param jewel Jewel value
 * @param cave  Set of jewels in the cave
 */
void Bag::take(int jewel, multiset<int> &cave)
{
	Iterator it = cave.find(jewel);
	
	if(it != cave.end())
		cave.erase(it);

	else
	{
		jewels.erase(jewels.find(jewel));
		amount -= jewel;

		if(! cave.empty())
		{
			it = cave.end();
			--it;

			amount += *it;
			jewels.insert(*it);
			cave.erase(it);
		}
	}
}

/**
 * Prints the total amount available in the bag
 * of Ali Baba every time that a jewel is left or taken
 * from the cave.
 * @return Execution status
 */
int main()
{
	int bag_size;
	cin >> bag_size;

	Bag bag(bag_size);
	multiset<int> cave;

	string action;
	int amount;

	while(cin >> action >> amount)
	{
		if(action == "leave")
			bag.leave(amount, cave);
		
		else
			bag.take(amount, cave);

		cout << bag.get_amount() << endl;
	}

	return 0;
}