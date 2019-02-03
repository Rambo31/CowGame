#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H



#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"


class GameOverState : public State
{
	public:
							GameOverState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		//sf::Sprite			mBackgroundSprite;
		sf::Text			mBlinkingText;
		sf::Text            mStableText;

		bool				mShowText;
		sf::Time			mTextEffectTime;
};
#endif // GAMEOVERSTATE_H
