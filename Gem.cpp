#include "Gem.hpp"
#include "Gem.hpp"
#include "Color.hpp"
#include "Size.hpp"
#include <iostream>
#include <string>
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

void Gem::printGem()
{
	//Bad solution, should be map, just want info on gem.
	std::string color;
	std::string size;
	int value = m_value;

	switch (m_color)
	{
		case Color::BLUE:
			color = "Blue";
			break;
		
		case Color::RED:
			color = "Red";
			break;

		case Color::YELLOW:
			color = "Yellow";
			break;

		case Color::PURPLE:
			color = "Purple";
			break;

		case Color::GREEN:
			color = "Green";
			break;
			
		default:
			color = "Undefined";
			break;
	}

	switch (m_size)
	{
		case Size::SMALL:
			size = "Small";
			break;

		case Size::LARGE:
			size = "Large";
			break;

		default:
			color = "Undefined";
			break;
	}

	std::cout << "Color: " << color << std::endl;
	std::cout << "Size : " << size << std::endl;
	std::cout << "Value: " << value << std::endl;
}
