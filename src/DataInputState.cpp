#include <SFML/Graphics/RenderWindow.hpp>

#include<iostream>

#include "DataInputState.h"
#include "Utility.h"
#include "ResourceHolder.h"

DataInputState::DataInputState(StateStack& stack, Context context)
: State(stack, context)
, mStableText()
, mName()
, mInputStr()
//, mShowText(true)
//, mTextEffectTime(sf::Time::Zero)
{
	//mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
    mStableText.setFont(context.fonts->get(Fonts::Sansation));
	mStableText.setString("Input your name -> ");
	mStableText.setPosition(64 , context.window->getView().getSize().y / 2.f );


	mName.setFont(context.fonts->get(Fonts::Sansation));
	mName.setPosition(mStableText.getPosition() + sf::Vector2f(mStableText.getGlobalBounds().width, 0));
}

void DataInputState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	//window.draw(mBackgroundSprite);

    window.draw(mStableText);
    window.draw(mName);

	/*if (mShowText)
		window.draw(mBlinkingText);*/
}

bool DataInputState::update(sf::Time dt)
{
	/*mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}*/

    mName.setString(mInputStr);

	return true;
}

bool DataInputState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{
	    if(event.key.code == sf::Keyboard::Return)
        {
            requestStackPop();
            requestStackPush(States::Game);
        }
        else if(event.key.code == sf::Keyboard::BackSpace && mInputStr.getSize() > 0)
        {
            mInputStr.erase(mInputStr.getSize() - 1);
        }
        else if(mInputStr.getSize() < 30)
        {
            if( event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z)
            {
                mInputStr += (char)(event.key.code + 97);
            }
            else if(event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9 )
            {
                mInputStr += (char)(event.key.code + 22);
            }
        }

	}


	return true;
}
