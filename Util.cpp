#include "Util.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "Gem.hpp"
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

std::vector<std::vector<int>> Util::cullIrregularities(std::vector<std::vector<int>> completeSets, std::map<int, Gem> gemMap, std::vector<Treasure> treasures)
{
	//Fetch each individual set
	//Fet matching treasure
	//Check that gem mapping matches size
	//If OK,

	//Current treasure to examine
	for (int i = 0; i < treasures.size(); i++)
	{

	}

	return std::vector<std::vector<int>>();
}
