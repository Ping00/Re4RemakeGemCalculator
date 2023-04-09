#include "Util.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "Gem.hpp"
#include "Size.hpp"
#include "Treasure.hpp"
void Util::makeCombinationUtil(std::vector<std::vector<int> >& ans, std::vector<int>& tmp, int n, int left, int k)
{
    // Pushing this vector to a vector of vector
    if (k == 0) {
        ans.push_back(tmp);
        return;
    }

    // i iterates from left to n. First time
    // left will be 1
    for (int i = left; i <= n; ++i)
    {
        tmp.push_back(i);
        makeCombinationUtil(ans, tmp, n, i + 1, k - 1);

        // Popping out last inserted element
        // from the vector
        tmp.pop_back();
    }
}

std::vector<std::vector<int>> Util::make_combinations(int n, int k)
{
    std::vector<std::vector<int> > ans;
    std::vector<int> tmp;
    makeCombinationUtil(ans, tmp, n, 1, k);
    return ans;
}

void Util::print_combinations(std::vector<std::vector<int>> ans)
{
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            std::cout << ans.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

void Util::recursiveTreasure(std::vector<std::vector<int>> presentGems, int currentVectorIndex, std::vector<std::vector<std::vector<int>>> vectorOfTreasures, std::vector<std::vector<std::vector<int>>> &treasureSets)
{
	//std::cout << "Recursive Treasure" << std::endl;

	//Is this the final layer
	bool finalLayer = false;
	if (currentVectorIndex + 1 == vectorOfTreasures.size())
	{
		//std::cout << "Final Layer!" << std::endl;
		finalLayer = true;
	}

	//Fetch current treasure in vector
	std::vector<std::vector<int>> currentTreasure = vectorOfTreasures[currentVectorIndex];
	
	//std::cout << "Examining Treasure " << currentVectorIndex + 1 << " of " << vectorOfTreasures.size() << std::endl;

	//std::cout << "Current treasure has: " << currentTreasure.size() << " combinations" << std::endl;
	//Iterate through combinations of the current treasure
	for (int i = 0; i < currentTreasure.size(); i++)
	{
		//Get current combination to check
		std::vector<int> currentCombination = currentTreasure[i];
		//std::cout << "Checking Combination : ";
		bool gemsOk = true;
		for (int j = 0; j < currentCombination.size(); j++)
		{
			int key = currentCombination[j];
			//std::cout << key << " ";
			
			//Check gempresent array if key matches any
			for (int k = 0; k < presentGems.size(); k++)
			{
				if (std::count(presentGems[k].begin(), presentGems[k].end(), key))
				{
					gemsOk = false;
					break;
				}
			}

		}


		if (gemsOk)
		{

			//std::cout << " Combination OK!";
			if (finalLayer)
			{
				//std::cout << " : Final Layer Adding Combination and saving set";
				//Create placeholder for gems (if we add the set to gems then continued iterations will fail)
				
				//Place all gems currently in presentGem to our final vector
				std::vector < std::vector<int>> newTreasureSet = {};
				for (int f = 0; f < presentGems.size(); f++)
				{
					newTreasureSet.push_back(presentGems[f]);
				}

				//Also push the final combination
				newTreasureSet.push_back(currentCombination);

				//Now push the new treasure set into the complete set
				treasureSets.push_back(newTreasureSet);
			}
			else
			{
				//Add gems to set and proceed to next iteration
				//std::cout << " Proceeding to deeper layer" << std::endl;
				//Create copy of presentGems
				std::vector<std::vector<int>> gemCopy = presentGems;
				gemCopy.push_back(currentCombination);
				recursiveTreasure(gemCopy, currentVectorIndex + 1, vectorOfTreasures, treasureSets);

				
			}
		}
		else
		{
			//std::cout << "GEMS ALREADY IN USE FOR THIS COMBINATION ";
		}

		//std::cout << std::endl;
	}

	return;
}

std::vector<std::vector<std::vector<int>>> Util::cullIrregularities(std::vector<std::vector<std::vector<int>>> completeSets, std::map<int, Gem> gemMap, std::vector<Treasure> treasures)
{

	//New final list containing all fully matching gem sets
	std::vector<std::vector<std::vector<int>>> newCombinationVector;

	//Iterate through list of possible combinations
	for (int i = 0; i < completeSets.size(); i++)
	{
		//Current combination set to investigate
		std::vector<std::vector<int>> currentSet = completeSets[i];
		
		//Keep track if set is ok to include
		bool setIsOk = true;

		//std::cout << "Combination #" << i + 1 << std::endl;
		
		//Iterate through all treasures the set includes
		for (int j = 0; j < currentSet.size(); j++)
		{
			//Fet the corresponding treasure from the vector
			Treasure currentTreasure = treasures[j];
			
			//Current combination for this treasure
			std::vector<int> currentCombination = currentSet[j];

			//Get amount of gems for the current treasure
			int currentTreasureSmallGemAmount = currentTreasure.get_gem_size_amount(Size::SMALL);
			int currentTreasureLargeGemAmount = currentTreasure.get_gem_size_amount(Size::LARGE);

			//What gems does the current combination contain?
			int currentCombinationSmallGems = 0;
			int currentCombinationLargeGems = 0;

			//Iterate through the combination values
			for (int k = 0; k < currentCombination.size(); k++)
			{
				//Map corresponding gem from int
				int currentValue = currentCombination[k];
				Gem mappedGem = gemMap.at(currentValue);

				//Get size of gem
				if (mappedGem.get_size() == Size::SMALL)
				{
					currentCombinationSmallGems++;
				}

				if (mappedGem.get_size() == Size::LARGE)
				{
					currentCombinationLargeGems++;
				}


				//std::cout << currentCombination[k] << std::endl;
			}

			//Check if gemcounts are OK
			//std::cout << "Treasure #" << j + 1 << "    [" << currentTreasureSmallGemAmount << "][" << currentTreasureLargeGemAmount << "]" << std::endl;
			//std::cout << "Combination #" << j + 1 << " [" << currentCombinationSmallGems << "][" << currentCombinationLargeGems << "]" << std::endl;
			
			if (currentTreasureLargeGemAmount !=currentCombinationLargeGems || currentCombinationSmallGems != currentTreasureSmallGemAmount)
			{
				setIsOk = false;
				break;
			}

		}

		if (setIsOk)
		{
			//std::cout << "Set is OK!" << std::endl;
			//std::cout << "Adding set to new vector" << std::endl;
			newCombinationVector.push_back(currentSet);
		}
		else
		{
			//std::cout << "SET IS BAD!!!!" << std::endl;
		}
	}

	return newCombinationVector;
}

std::vector<std::vector<int>> Util::calculateHighestCombination(std::vector<std::vector<std::vector<int>>> completeSets, std::map<int, Gem> gemMap, std::vector<Treasure> treasures)
{
	//Iterates through the vector
	//Maps the number to a gem we have in our possession
	//This list is fed into the Treasure which will tell us its actual value with this proposed combination
	//Do this for every provided complete set, and print final values

	//Variables to keep track of best set
	int bestValue = 0;
	std::vector<std::vector<int>> bestSet;

	//Iterate through all provided sets
	for (int i = 0; i < completeSets.size(); i++)
	{
		//Current set we are calculating;
		std::vector<std::vector<int>> currentSet = completeSets[i];

		//List of gems which match the currentSet structure
		std::vector<std::vector<Gem>> currentGems;

		//Get current set combinations
		for (int j = 0; j < currentSet.size(); j++)
		{
			std::vector<int> currentCombination = currentSet[j];

			std::vector<Gem> gemsInThisCombination;

			//Iterate through the combination
			for (int k = 0; k < currentCombination.size(); k++)
			{
				//Find the matching gem
				int currentValue = currentCombination[k];
				Gem mappedGem = gemMap.at(currentValue);

				//Add the gem to the currentCombination vector
				gemsInThisCombination.push_back(mappedGem);
			}

			//Push the gems to the currentGems vector
			currentGems.push_back(gemsInThisCombination);
		}

		int currentTreasureValue = 0;
		//Now compare treasures and Gemlists to get value of gems
		for (int t = 0; t < treasures.size(); t++)
		{
			currentTreasureValue += treasures[t].get_value(currentGems[t]);
		}

		if (currentTreasureValue > bestValue)
		{
			std::cout << "Combination #" << i + 1 << " is the current best combination at: " << currentTreasureValue << std::endl;
			
			bestValue = currentTreasureValue;
			bestSet = currentSet;
		}

	}

	std::cout << "Best Value is: " << bestValue << std::endl;

	return bestSet;
}
