#ifndef BESTSCORESSTATE_H
#define BESTSCORESSTATE_H

#include <SFML/Graphics/Text.hpp>

#include<utility>
#include<vector>

#include "State.h"


class BestScoresState : public State
{
	public:
							BestScoresState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);

    private:
        void                sortResults();
	private:
    std::vector<std::pair<sf::String, sf::String>> mData;
	sf::Text                mNames;
	sf::Text                mScores;
	sf::Text                mResults;
};

#endif // BESTSCORESSTATE_H
