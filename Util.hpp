#ifndef __UTIL_HPP__
#define __UTIL_HPP__
#include <vector>
class Util
{
	private:
		static void makeCombinationUtil(std::vector<std::vector<int> >& ans, std::vector<int>& tmp, int n, int left, int k);
	public:
		static std::vector<std::vector<int>> make_combinations(int n, int k);
		static void print_combinations(std::vector<std::vector<int>> combinations);
};
#endif // !__UTIL_HPP__

