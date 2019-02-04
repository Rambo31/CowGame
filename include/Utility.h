#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED


#include <sstream>
#include<string>
#include<vector>

namespace sf
{
	class Sprite;
	class Text;
}


void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

void writeScoreToFile(std::string name, unsigned int score, sf::String filename);
void readEntryFromFile(std::vector<std::pair<sf::String, sf::String>>& vect, sf::String filename);

#endif // UTILITY_H_INCLUDED
