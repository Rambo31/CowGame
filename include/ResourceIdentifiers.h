#ifndef RESOURCEIDENTIFIERS_H_INCLUDED
#define RESOURCEIDENTIFIERS_H_INCLUDED

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
}

namespace Textures
{
	enum ID
	{
	    Cow
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // RESOURCEIDENTIFIERS_H_INCLUDED
