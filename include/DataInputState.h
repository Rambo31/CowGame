#ifndef DATAINPUTSTATE_H
#define DATAINPUTSTATE_H




#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"


class DataInputState : public State
{
	public:
							DataInputState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		//sf::Sprite			mBackgroundSprite;
		sf::Text            mStableText;
		sf::Text            mName;
        sf::String          mInputStr;
		//bool				mShowText;
		//sf::Time			mTextEffectTime;
};
#endif // DATAINPUTSTATE_H
