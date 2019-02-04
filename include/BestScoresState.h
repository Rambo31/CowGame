#ifndef BESTSCORESSTATE_H
#define BESTSCORESSTATE_H

#include <SFML/Graphics/Text.hpp>

#include "State.h"


class BestScoresState : public State
{
	public:
							BestScoresState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:

	sf::Text                mNames;
	sf::Text                mScores;
};

#endif // BESTSCORESSTATE_H
