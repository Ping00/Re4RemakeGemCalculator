#include "Gem.hpp"
#include "Gem.hpp"
#include "Color.hpp"
#include "Size.hpp"
Gem::Gem(int value, Color color, Size size)
{
	m_value = value;
	m_color = color;
	m_size = size;
}

Gem::~Gem()
{

}

Color Gem::get_color()
{
	return m_color;
}

int Gem::get_value()
{
	return m_value;
}

Size Gem::get_size()
{
	return m_size;
}