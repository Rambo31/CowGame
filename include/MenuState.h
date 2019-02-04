#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


#include "State.h"

class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);

		void					updateOptionText();


	private:
		enum OptionNames
		{
			Play,
			Scores,
			Exit,
		};


	private:
		//sf::Sprite				mBackgroundSprite;

		std::vector<sf::Text>	mOptions;
		std::size_t				mOptionIndex;
};


#endif // MENUSTATE_H
