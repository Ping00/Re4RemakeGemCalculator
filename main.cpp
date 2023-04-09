#include <iostream>
#include "Gem.hpp"
#include "Size.hpp"
#include "Color.hpp"
#include <vector>
#include "Treasure.hpp"
#include "Util.hpp"
#include <map>
#include <tuple>
int main(int argc, char* argv[])
{

	//THIS IS A BRUTE FORCE SOLUTION 

	/*
	//Gem Types
	Gem red_small		= Gem(3000, Color::RED,		Size::SMALL);
	Gem blue_small		= Gem(4000, Color::BLUE,	Size::SMALL);
	Gem yellow_small	= Gem(7000, Color::YELLOW,	Size::SMALL);
	Gem green_large		= Gem(5000, Color::GREEN,	Size::LARGE);
	Gem purple_large	= Gem(6000, Color::PURPLE,	Size::LARGE);
	Gem red_large		= Gem(9000, Color::RED,		Size::LARGE);
	Gem empty			= Gem(0,	Color::NONE,	Size::NONE);

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

	const int n = 8;	//Total Gems in calculation
	const int k1 = 2;	//Total slots in first treasure
	const int k2 = 2;	//Total slots in secondary treasure
	//const int k3 = 2;	//Total slots in secondary treasure
	std::vector<std::vector<int>> firstTreasure = Util::make_combinations(n, k1);
	std::vector<std::vector<int>> secondTreasure = Util::make_combinations(n, k2);
	//std::vector<std::vector<int>> thirdTreasure = Util::make_combinations(n, k3);

	std::cout << "Combinations for First treasure: " << firstTreasure.size() << std::endl;

	Util::print_combinations(firstTreasure);
	std::cout << "----" << std::endl;
	Util::print_combinations(secondTreasure);

	//This vector contains a vector of all our treasures, which contain a vector that contain all our combinations
	//List of Treasures >> List of Combinations >> Value of combination
	std::vector<std::vector<std::vector<int>>> vectorOfTreasures = {};
	vectorOfTreasures.push_back(firstTreasure);
	vectorOfTreasures.push_back(secondTreasure);
	//vectorOfTreasures.push_back(thirdTreasure);

	//STEP 2
	//Generate groups of possible treasure
	//Treasure A has two slots and B has 3 slots, and gems are noted as (1,2,3,4,5)
	//For every A create B which has no overlap in gem numbers
	//This can be done by selecting each combination which is not present in the previous treasure
	//this can be done up to n treasures

	//All Possible sets of treasure
	std::vector<std::vector<std::vector<int>>> treasureSets = {};

	//Empty vector as default entry point
	std::vector<std::vector<int>> presentGems = {};
	int currentIndex = 0;
	
	std::cout << "TreasureSets Before creation: " << treasureSets.size() << std::endl;

	Util::recursiveTreasure(presentGems, currentIndex, vectorOfTreasures, treasureSets);

	std::cout << "TreasureSets After creation: " << treasureSets.size() << std::endl;

	/*
	for (int i = 0; i < treasureSets.size(); i++)
	{
		std::vector<std::vector<int>> currentTreasure = treasureSets[i];
		for (int j = 0; j < currentTreasure.size(); j++)
		{
			std::vector<int> treasureCombination = currentTreasure[j];
			for (int k = 0; k < treasureCombination.size(); k++)
			{
				std::cout << treasureCombination[k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "------" << std::endl;
	}
	*/

	//All Possible Gems
	Gem red_small = Gem(3000, Color::RED, Size::SMALL);
	Gem blue_small = Gem(4000, Color::BLUE, Size::SMALL);
	Gem yellow_small = Gem(7000, Color::YELLOW, Size::SMALL);
	Gem green_large = Gem(5000, Color::GREEN, Size::LARGE);
	Gem purple_large = Gem(6000, Color::PURPLE, Size::LARGE);
	Gem red_large = Gem(9000, Color::RED, Size::LARGE);
	Gem undefined = Gem(0, Color::NO_COLOR, Size::NO_SIZE);


	//Step 3
	//Assign a gem to each numeric value equal to gems in possession
	//(If fewer gems are used than there are available slots then the remainders will be filled with 'duds')
	//After gems have been assigned, Assign treasure gem sizes as well to selected treasures.
	std::map<int, Gem> gemMap = {};

	//This would be loaded from outside
	std::vector<Gem> gemsUsed = 
	{ 
		red_small,
		red_small,
		red_large, 
		blue_small, 
		blue_small,
		blue_small,
		yellow_small,
		yellow_small
	};
	
	for (int i = 0; i < gemsUsed.size(); i++)
	{
		gemMap.insert(std::make_pair(i + 1, gemsUsed[i]));
	}

	//Treasures we have selected
	Treasure flagon = Treasure(4000, 2, 0);
	Treasure bangle = Treasure(4000, 2, 0);

	//Defining list of treasures (Should also be loaded from outside
	std::vector<Treasure> treasuresUsed = {
		flagon, 
		bangle
	};

	//Note that treasures will always retain their order from the initial list.

	//Step 4
	//Second pass, pass every defined combination set once more with these new rules
	//Sets with Gems that do not match the indicated sizes will become invalidated
	
	

	//Step 5 Calculate total value of each Set, Highest one is the best available one.



	return 0;
}