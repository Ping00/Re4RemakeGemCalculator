#include <iostream>
#include "Gem.hpp"
#include "Size.hpp"
#include "Color.hpp"
#include <vector>
#include "Treasure.hpp"
#include "Util.hpp"
#include <map>
int main(int argc, char* argv[])
{
	/*
	//Gem Types
	Gem red_small		= Gem(3000, Color::RED,		Size::SMALL);
	Gem blue_small		= Gem(4000, Color::BLUE,	Size::SMALL);
	Gem yellow_small	= Gem(7000, Color::YELLOW,	Size::SMALL);
	Gem green_large		= Gem(5000, Color::GREEN,	Size::LARGE);
	Gem purple_large	= Gem(6000, Color::PURPLE,	Size::LARGE);
	Gem red_large		= Gem(9000, Color::RED,		Size::LARGE);

	Treasure flagon = Treasure(4000, 2, 0);
	Treasure bangle = Treasure(4000, 0, 2);


	std::vector<Gem> test;
	test.push_back(blue_small);
	test.push_back(yellow_small);


	//2RS 12000 Duo
	//1B1Y 16500 two_color bonus

	std::cout << "Treasure Multiplier: " << flagon.get_multiplier(test) << std::endl;
	std::cout << "Treasure Value: " << flagon.get_value(test) << std::endl;

	//test.push_back(yellow_small);

	Treasure tempTreasure = Treasure(4000, 2, 0);
	//tempTreasure.get_multiplier(test);

	//tempTreasure.find_optimal_value();

	//Gem Combos
	float two_colors = 1.1;
	float duo = 1.2;
	float three_colors = 1.3;
	float trio = 1.4;
	float two_duos = 1.5;
	float four_colors = 1.6;
	float quartet = 1.7;
	float duo_and_trio = 1.8;
	float quintet = 1.9;
	float five_colors = 2.0;

	int n = 7; //Gems
	int k = 3; //Slots
	std::vector<std::vector<int> > ans = Util::make_combinations(n, 3);
	std::vector<std::vector<int> > ans2 = Util::make_combinations(n, 2);
	Util::print_combinations(ans);
	Util::print_combinations(ans2);

	for (int i = 0; i < ans.size(); i++)
	{
		for (int x : ans[i])
		{
			std::cout << x;
		}
		std::cout << std::endl;
	}


	//NEW SOLUTION

		//Small Ruby 3000
		//Small Sapphire 4000
		//Small Diamond 7000
		//Large Emerald 5000
		//Large Amethyst 6000
		//Large Ruby 9000
	*/

	//New Solution

	//STEP 1
	//Generate combinations of all selected treasures and gemstones
	//Only amount of gemstones and treasure slots required, type of gemstones will be defined later
	//As this is just a combinatorics problem.
	//PSA: Requires that: gemstones >= treasure slots
	
	//NOTE! we can fill in any leftover slots if we fill the identity list with 'duds' when we do the final validation so 
	//n should always be >= k regardless of actual gems in possession, these combinations will simply be invalidated later.

	const int n = 5;	//Total Gems in calculation
	const int k1 = 2;	//Total slots in first treasure
	const int k2 = 3;	//Total slots in secondary treasure
	std::vector<std::vector<int>> flagonCombinations = Util::make_combinations(n, k1);
	std::vector<std::vector<int>> maskCombinations = Util::make_combinations(n, k2);

	//This vector contains a vector of all our treasures, which contain a vector that contain all our combinations
	//List of Treasures >> List of Combinations >> Value of combination
	std::vector<std::vector<std::vector<int>>> treasureCollection = {};

	//Temp print
	Util::print_combinations(flagonCombinations);
	std::cout << "-------" << std::endl;
	Util::print_combinations(maskCombinations);

	//STEP 2
	//Generate groups of possible treasure
	//Treasure A has two slots and B has 3 slots, and gems are noted as (1,2,3,4,5)
	//For every A create B which has no overlap in gem numbers
	//This can be done by selecting each combination which is not present in the previous treasure
	//this can be done up to n treasures


	//Maskcombinations go first as since it takes most slots it will produce the least amount of possible sets of treasure
	//2:3 order will result in 4 total combinations, 3:2 will result in 3

	//List container a list of all possible treasure sets that the gems will allow
	std::vector<std::vector<std::vector<int>>> treasureSets = {};
	for (int i = 0; i < maskCombinations.size(); i++)
	{
		//Current gems used
		std::vector<int> gemsUsedMask = maskCombinations[i];

		std::cout << "Examining current mask combination: ";
		for (int value : gemsUsedMask)
		{
			std::cout << value;
		}
		std::cout << std::endl;

		//Iterate through other treasure combinations
		for (int j = 0; j < flagonCombinations.size(); j++)
		{

			//Current gems used
			std::vector<int> gemsUsedFlagon = flagonCombinations[j];

			std::cout << "Examining current flagon combination: [";
			for (int value : gemsUsedFlagon)
			{
				std::cout << value;
			}
			std::cout << "] ";

			
			//value is key
			bool gemCombinationValid = true;
			for (int value : gemsUsedFlagon)
			{
				if (std::count(gemsUsedMask.begin(), gemsUsedMask.end(), value) == true)
				{
					//std::cout << "Contained Gem " << value << std::endl;
					gemCombinationValid = false;
					break;
				}
			}

			if (gemCombinationValid)
			{
				//Current mask and flagon combination valid
				std::cout << "Valid combination for mask and flagon";

				//Insert combination into list
				
				//Create new treasure set
				treasureSets.push_back(std::vector<std::vector<int>>());
				treasureSets[i].push_back(gemsUsedMask);
				treasureSets[i].push_back(gemsUsedFlagon);

			}
			std::cout << std::endl;
		}
	}

	//Map every gem to a gem existing in the game


	std::cout << "Contains #" << treasureSets.size() << " Sets of possible treasure combinations" <<std::endl;
	for (int i = 0; i < treasureSets.size(); i++)
	{
		std::cout << "Set contains #" << treasureSets[i].size() << std::endl;
	}

	//Map each value from the treasureSets to an actual gemstone
	std::map<int, Gem> gemMap;

	//Create a list which contains our ACTUAL gemstones
	//1 = Small Red (Ruby)
	//2 = Small Red (Ruby)
	//3 = Small Blue (Sapphire)
	//4 = Small Yellow (Diamond)
	//5 = Large Green (Emerald)
	//6 = Large Purple (Alexandrite)

	return 0;
}