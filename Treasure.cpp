#include "Treasure.hpp"
#include <vector>
#include "Color.hpp"
#include <iostream>
#include <algorithm>
Treasure::Treasure(int value, int small_gems, int large_gems)
{
	m_value = value;
	m_small_gems = small_gems;
	m_large_gems = large_gems;
}

Treasure::~Treasure()
{

}

float Treasure::get_multiplier(std::vector<Gem> gemstones)
{
	//Vector to hold all colors
	std::vector<int> colors_present(5);

	//Sort gems into their respective color categories
	for (int i = 0; i < gemstones.size(); i++)
	{
		switch (gemstones.at(i).get_color())
		{
			case Color::RED:
				colors_present.at(0) += 1;
				break;

			case Color::BLUE:
				colors_present.at(1) += 1;
				break;

			case Color::YELLOW:
				colors_present.at(2) += 1;
				break;

			case Color::GREEN:
				colors_present.at(3) += 1;
				break;

			case Color::PURPLE:
				colors_present.at(4) += 1;
				break;

			default:
				break;
		}
	}

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

	//Gem counters
	int single_gem_counter = 0;
	int double_gem_counter = 0;
	int triple_gem_counter = 0;
	int quadruple_gem_counter = 0;
	int quintet_gem_counter = 0;

	//Count gems based on their color amounts
	for (int i = 0; i < colors_present.size(); i++)
	{
		switch (colors_present.at(i))
		{
			case 1:
				single_gem_counter++;
				break;

			case 2:
				double_gem_counter++;
				break;

			case 3:
				triple_gem_counter++;
				break;

			case 4:
				quadruple_gem_counter++;
				break;

			case 5:
				quintet_gem_counter++;
				break;

			default:
				break;
		}
	}

	//2 Gem checks
	if (gemstones.size() == 2)
	{
		//Two color check
		if (single_gem_counter == 2)
		{
			return two_colors;
		}
		
		//Duo check
		if (double_gem_counter == 1)
		{
			return duo;
		}
	}
	
	//3 Gem Checks
	if (gemstones.size() == 3)
	{
		//Three colors
		if (single_gem_counter == 3)
		{
			return three_colors;
		}

		//Trio
		if (triple_gem_counter == 1)
		{
			return trio;
		}
	}

	//4 Gem Checks
	if (gemstones.size() == 4)
	{
		//Two Duos
		if (double_gem_counter == 2)
		{
			return two_duos;
		}

		//Four colors
		if (single_gem_counter == 4)
		{
			return four_colors;
		}

		//Quartet
		if (quadruple_gem_counter == 4)
		{
			return quartet;
		}
	}

	//5 Gem Checks
	if (gemstones.size() == 5)
	{
		//Duo & Trio
		if (double_gem_counter == 1 && triple_gem_counter == 1)
		{
			return duo_and_trio;
		}

		//Quintet
		if (quintet_gem_counter == 1)
		{
			return two_colors;
		}

		//Five Colors
		if (single_gem_counter == 5)
		{
			return five_colors;
		}
	}

	return 1;
}

int Treasure::get_value(std::vector<Gem> gemstones)
{
	//Base value of treasure
	int totalValue = m_value;

	//Add all gemstone values
	for (int i = 0; i < gemstones.size(); i++)
	{
		totalValue += gemstones.at(i).get_value();
	}

	//Multiply with gemstone combo
	float multiplier = get_multiplier(gemstones);

	return totalValue * multiplier;
}

void Treasure::find_optimal_value()
{
	
	//All Gem Types
	Gem red_small = Gem(3000, Color::RED, Size::SMALL);
	Gem blue_small = Gem(4000, Color::BLUE, Size::SMALL);
	Gem yellow_small = Gem(7000, Color::YELLOW, Size::SMALL);
	Gem green_large = Gem(5000, Color::GREEN, Size::LARGE);
	Gem purple_large = Gem(6000, Color::PURPLE, Size::LARGE);
	Gem red_large = Gem(9000, Color::RED, Size::LARGE);

	//all gems vector
	std::vector<Gem> all_gems = {};
	all_gems.push_back(red_small);
	all_gems.push_back(blue_small);
	all_gems.push_back(yellow_small);
	all_gems.push_back(green_large);
	all_gems.push_back(purple_large);
	all_gems.push_back(red_large);

	std::vector<int> slots = { 1,2 };
	std::vector<int> gems = { 1,2,3 };

	int total_slots = m_small_gems + m_large_gems;

	std::cout << "Gems: " << total_slots << std::endl;

	std::vector<std::vector<Gem>> gem_permutations = {};

	std::vector<std::vector<int>> temp;
	temp.reserve(100);

	//1,1
	//1,2
	//2,1
	//2,2

	if (total_slots == 2)
	{

		//2 Slots with 6 gems can have a max of 36 combinations
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				//New vector
				gem_permutations.push_back(std::vector<Gem>());
				gem_permutations[6 * i + j].push_back(all_gems.at(i));
				gem_permutations[6 * i + j].push_back(all_gems.at(j));
			}
		}

		std::cout << "Current Permutations = " << gem_permutations.size() << std::endl;
		for (int i = 0; i < gem_permutations.size(); i++)
		{
			std::cout << "Gem Details..." << std::endl;
			for (int j = 0; j < gem_permutations[i].size(); j++)
			{
				Color color = gem_permutations[i][j].get_color();
				int value = gem_permutations[i][j].get_value();
				Size size = gem_permutations[i][j].get_size();

				std::cout << "Color [" << color << "] | Value: " << value  << " || Size : " << size << std::endl;
			}

			std::cout << std::endl;
		}

		std::cout << "Looking for following gem combination: [" << m_small_gems << "][" << m_large_gems << "]" << std::endl;

		//Perform culling of unmatching sets of gemstones
		for (int i = 0; i < gem_permutations.size(); i++)
		{
			//int large_gems = get_gem_size_amount(gem_permutations[i], Size::LARGE);
			//int small_gems = get_gem_size_amount(gem_permutations[i], Size::SMALL);



			//std::cout << "Permutation Small|Large : [" << small_gems << "][" << large_gems << "]" << std::endl;

			/*
			if (m_large_gems != large_gems || m_small_gems != small_gems)
			{
				std::cout << "Culling entry due to wrong gem count; from set" << std::endl;
				gem_permutations.erase(gem_permutations.begin() + i);
			}
			*/


		}

		std::cout << "Current Permutations after culling: " << gem_permutations.size() << std::endl;




	}

	/*
	//2 Slots with 6 gems can have a max of 36 combinations
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			//New vector
			temp.push_back(std::vector<int>());
			temp[6 * i + j].push_back(i+1);
			temp[6 * i + j].push_back(j+1);
		}

	}


	std::cout << "Vectors:" << temp.size() << std::endl;

	//array[width * row + col] = value;
	//2 * i + j

	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << "Vectors Within Vector:" << temp[i].size() << std::endl;
		for (int j = 0; j < temp[i].size(); j++)
		{
			std::cout << "[" << temp[i][j] << "]";
		}
		std::cout << std::endl;

	}
	*/
	//1,1
	//1,2
	//1,3
	//1,4
	//1,5
	//1,6



}

int Treasure::get_gem_size_amount(Size size)
{
	if (size == Size::SMALL)
	{
		return m_small_gems;
	}
	else if (Size::LARGE)
	{
		return m_large_gems;
	}

	return 0;
}

int Treasure::getTotalSlots()
{
	return m_small_gems + m_large_gems;
}
