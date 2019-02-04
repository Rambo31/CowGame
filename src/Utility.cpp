#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Utility.h"

#include <cmath>
#include <fstream>
#include<iostream>


void writeScoreToFile(std::string name, unsigned int score, sf::String filename)
{
    std::ofstream out;

    out.open(filename, std::ios::app);

    if(out.is_open())
    {
        out<<name<<'='<<score<<std::endl;
    }

    out.close();
}

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}
