#ifndef __TREASURE_HPP__
#define __TREASURE_HPP__
#include <vector>
#include "Gem.hpp"
class Treasure
{
	private:
		int m_small_gems;
		int m_large_gems;
		int m_value;

	public:
		Treasure(int value, int small_gems, int large_gems);
		~Treasure();
		float get_multiplier(std::vector<Gem> gemstones);
		int get_value(std::vector<Gem> gemstones);
		void find_optimal_value();

		int get_gem_size_amount(Size size);
		int getTotalGems();
		
};
#endif // !__HPP_TREASURE__

