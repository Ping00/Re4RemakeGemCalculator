#ifndef __GEM_HPP__
#define __GEM_HPP__
#include "Color.hpp"
#include "Size.hpp"
class Gem
{
	private:
		int m_value;
		Color m_color;
		Size m_size;

	public:
		Gem(int value, Color color, Size size);
		~Gem();
		Color get_color();
		int get_value();
		Size get_size();
};
#endif // !__GEM_HPP__

