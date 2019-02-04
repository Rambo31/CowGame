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

void readEntryFromFile(std::vector<std::pair<sf::String, sf::String>>& vect, sf::String filename)
{
    sf::String name = "";
    sf::String number = "";

    std::ifstream in(filename);

    if(in.is_open())
    {
        char ch;

        while(in.peek() != EOF)
        {
            while((ch = in.get()) && ch != '=')
            {
                name += ch;
            }


            while((ch = in.get()) && ch != '\n')
            {
                number += ch;
            }

            vect.push_back(std::make_pair(name, number));
            name.clear();
            number.clear();
        }
    }
    in.close();


}
