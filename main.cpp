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
	//THIS IS A BRUTE FORCE SOLUTION 

	//Constant values for components
	//These should be loaded from a file or something

	//Treasures
	const Treasure flagon	= Treasure(4000, 2, 0);
	const Treasure bangle	= Treasure(4000, 2, 0);
	const Treasure clock	= Treasure(4000, 1, 1);

	//Gemstones
	const Gem redSmall		= Gem(3000,	Color::RED,			Size::SMALL);
	const Gem blueSmall		= Gem(4000, Color::BLUE,		Size::SMALL);
	const Gem yellowSmall	= Gem(7000, Color::YELLOW,		Size::SMALL);
	const Gem greenLarge	= Gem(5000, Color::GREEN,		Size::LARGE);
	const Gem purpleLarge	= Gem(6000, Color::PURPLE,		Size::LARGE);
	const Gem redLarge		= Gem(9000, Color::RED,			Size::LARGE);
	const Gem undefined		= Gem(0,	Color::NO_COLOR,	Size::NO_SIZE);

	//Step 1: Select Treasures to be used in calculation
	 
	std::vector<Treasure> selectedTreasures = {
		flagon,
		bangle,
		clock
	};

	//Step 2: Select Gems to be used in calculation
	std::vector<Gem> selectedGems =
	{
		redSmall,
		blueSmall,
		blueSmall,
		blueSmall,
		yellowSmall,
		redLarge,
		greenLarge,
	};

	//Should our selected gems be < than the total amount of slots on our treasures;
	//Then the remaining slots will be filled with 'duds' having no value.
	const int totalSelectedGems = selectedGems.size();
	const int totalSlotsAllTreasures = Util::getTotalSlots(selectedTreasures);

	//Should the amount of gems be < than the total amount of empty slots, then the remainders will be filled with placeholder empty gems
	if (totalSelectedGems < totalSlotsAllTreasures)
	{
		std::cout << "Too few gems:" << totalSelectedGems << std::endl;
		const int missingGems = totalSlotsAllTreasures - totalSelectedGems;
		std::cout << "Missing Gems:" << missingGems << std::endl;
		//Insert undefined gems to fill any empty slots
		for (int i = 0; i < missingGems; i++)
		{
			selectedGems.push_back(undefined);
			std::cout << "Adding Gem.." << std::endl;
		}
	}
	
	std::cout << "Gems now Present:" << selectedGems.size() << std::endl;

	//Step 3: Generate combinations available for each treasure using selected gems
	//Treasure >> Vector of Combinations >> Value of Combination
	std::vector<std::vector<std::vector<int>>> vectorOfAllTreasureCombinations = {};

	//For each treasure, calculate the amount of combinations using n & k
	//n = total amount of gems used
	//k = the amount of slots the treasure has.
	for (int i = 0; i < selectedTreasures.size(); i++)
	{
		const int n = selectedGems.size();
		const int k = selectedTreasures[i].getTotalSlots();
		std::vector<std::vector<int>> treasureCombinations = Util::make_combinations(n, k);
		vectorOfAllTreasureCombinations.push_back(treasureCombinations);
	}

	//Step 4: Calculate all possible matching sets where gems do not overlap

	//All Possible sets of treasure
	std::vector<std::vector<std::vector<int>>> possibleTreasureSets = {};

	//Empty gem vector which we examine if we have any mathces in the current vector
	std::vector<std::vector<int>> presentGems = {};
	
	//Counter to see which index we are in
	int layerIndex = 0;

	std::cout << "TreasureSets Before creation: " << possibleTreasureSets.size() << std::endl;

	//Recursively examine each treasure and add any combinations without overlap into possibleTreasureSets
	Util::recursiveTreasure(presentGems, layerIndex, vectorOfAllTreasureCombinations, possibleTreasureSets);

	std::cout << "TreasureSets After creation: " << possibleTreasureSets.size() << std::endl;

	//Step 5: Assign each numerical value from the treasureSets to a Gem

	//Map which corresponds to each numerical value in the combinations vectors
	std::map<int, Gem> gemMap = {};
	for (int i = 0; i < selectedGems.size(); i++)
	{
		//Combinations start counting at 1
		gemMap.insert(std::make_pair(i + 1, selectedGems[i]));
	}

	//Step 5: Re-examine the list of possible sets and remove all invalid gem combinations
	//E.g. A clock can only hold a Large and small gem, not two large or two small.
	//So those combinations cannot be used.
	
	//New vector containing only valid sets
	std::vector<std::vector<std::vector<int>>> treasureCombinationsWithoutInvalidGems = Util::removeInvalidSets(possibleTreasureSets, gemMap, selectedTreasures);

	std::cout << "Set Count after removing invalid gem combinations #" << treasureCombinationsWithoutInvalidGems.size() << std::endl;

	//Step 6: Calculate remaining values with provided gem combinations and determine best one.
	std::vector<std::vector<int>> bestSet = Util::calculateHighestCombination(treasureCombinationsWithoutInvalidGems, gemMap, selectedTreasures);

	std::cout << "The best gem combination is the following:" << std::endl << std::endl;

	std::vector<std::vector<int>> currentTreasure = bestSet;
	for (int j = 0; j < currentTreasure.size(); j++)
	{
		std::vector<int> treasureCombination = currentTreasure[j];
		std::cout << "Treasure #" << j + 1 << std::endl;
		for (int k = 0; k < treasureCombination.size(); k++)
		{
			//
			Gem gem = gemMap.at(treasureCombination[k]);
			gem.printGem();
			//std::cout << treasureCombination[k] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "------" << std::endl;

	return 0;
}