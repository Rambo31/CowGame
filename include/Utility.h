#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED


#include <sstream>


namespace sf
{
	class Sprite;
	class Text;
}


void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);


#endif // UTILITY_H_INCLUDED
