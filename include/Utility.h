#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED


#include <sstream>
#include<string>

namespace sf
{
	class Sprite;
	class Text;
}


void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

void writeScoreToFile(std::string name, unsigned int score, sf::String filename);

#endif // UTILITY_H_INCLUDED
