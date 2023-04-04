#include <iostream>
#include "Gem.hpp"
#include "Size.hpp"
#include "Color.hpp"
#include <vector>
#include "Treasure.hpp"
int main(int argc, char* argv[])
{
	//Gem Types
	Gem red_small		= Gem(3000, Color::RED,		Size::SMALL);
	Gem blue_small		= Gem(4000, Color::BLUE,	Size::SMALL);
	Gem yellow_small	= Gem(7000, Color::YELLOW,	Size::SMALL);
	Gem green_large		= Gem(5000, Color::GREEN,	Size::LARGE);
	Gem purple_large	= Gem(6000, Color::PURPLE,	Size::LARGE);
	Gem red_large		= Gem(9000, Color::RED,		Size::LARGE);

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
	tempTreasure.get_multiplier(test);

	tempTreasure.find_optimal_value();

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



	/*
Small Ruby 3000
Small Sapphire 4000
Small Diamond 7000
Large Emerald 5000
Large Amethyst 6000
Large Ruby 9000
	*/

	return 0;
}