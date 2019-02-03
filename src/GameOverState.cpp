#include <SFML/Graphics/RenderWindow.hpp>


#include "GameOverState.h"
#include "Utility.h"
#include "ResourceHolder.h"

GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mBlinkingText()
, mStableText()
, mShowText(true)
, mTextEffectTime(sf::Time::Zero)
{
	//mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
    mStableText.setFont(context.fonts->get(Fonts::Sansation));
	mStableText.setString("GAME OVER");
	centerOrigin(mStableText);
	mStableText.setPosition(context.window->getView().getSize() / 2.f);


	mBlinkingText.setFont(context.fonts->get(Fonts::Sansation));
	mBlinkingText.setString("Press any key to continue");
	centerOrigin(mBlinkingText);
	mBlinkingText.setPosition(mStableText.getPosition() + sf::Vector2f(0, 40.f));
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	//window.draw(mBackgroundSprite);

    window.draw(mStableText);

	if (mShowText)
		window.draw(mBlinkingText);
}

bool GameOverState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}
