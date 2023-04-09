#ifndef __UTIL_HPP__
#define __UTIL_HPP__
#include <vector>
#include <map>
#include "Gem.hpp"
#include "Treasure.hpp"
class Util
{
	private:
		static void makeCombinationUtil(std::vector<std::vector<int> >& ans, std::vector<int>& tmp, int n, int left, int k);
	public:
		static std::vector<std::vector<int>> make_combinations(int n, int k);
		static void print_combinations(std::vector<std::vector<int>> combinations);

		static void recursiveTreasure(std::vector<std::vector<int>> presentGems, int currentVectorIndex, std::vector<std::vector<std::vector<int>>> vectorOfTreasures, std::vector<std::vector<std::vector<int>>> &treasureSets);
		static std::vector<std::vector<std::vector<int>>> removeInvalidSets(std::vector<std::vector<std::vector<int>>> completeSets, std::map<int,Gem> gemMap, std::vector<Treasure> treasures);
		static std::vector<std::vector<int>> calculateHighestCombination(std::vector<std::vector<std::vector<int>>> completeSets, std::map<int, Gem> gemMap, std::vector<Treasure> treasures);
		static int getTotalSlots(std::vector<Treasure>);
};
#endif // !__UTIL_HPP__

