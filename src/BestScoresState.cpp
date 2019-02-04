#include <SFML/Graphics/RenderWindow.hpp>


#include "BestScoresState.h"
#include "Utility.h"
#include "ResourceHolder.h"

BestScoresState::BestScoresState(StateStack& stack, Context context)
: State(stack, context)
, mNames()
, mScores()
{
    mNames.setFont(context.fonts->get(Fonts::Sansation));
	mNames.setString("NAME");
	centerOrigin(mNames);
	mNames.setPosition(context.window->getView().getSize().x / 2.f - 256.f, 64.f);

    mScores.setFont(context.fonts->get(Fonts::Sansation));
	mScores.setString("SCORE");
	centerOrigin(mScores);
	mScores.setPosition(context.window->getView().getSize().x / 2.f + 256.f, 64.f);
}

void BestScoresState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mNames);
	window.draw(mScores);
}

bool BestScoresState::update(sf::Time dt)
{

	return true;
}

bool BestScoresState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}
