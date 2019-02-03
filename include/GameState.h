#ifndef GAMESTATE_H
#define GAMESTATE_H



#include<SFML/Window/Keyboard.hpp>
#include<SFML/Window/Event.hpp>

#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Graphics/Font.hpp>

#include"State.h"
#include"ResourceHolder.h"
#include"ResourceIdentifiers.h"
#include"Flower.h"
#include"Cow.h"

class GameState : public State
{
	public:
								GameState(StateStack& stack, Context context);
                                ~GameState();
virtual	void				    draw();
virtual	bool			        update(sf::Time elapsedTime);
virtual	bool				    handleEvent(const sf::Event& event);

	private:
	    void                    generateFlower(); //world

        void                    loadFonts();
        void                    loadTextures(); //world
        void                    buildScene();//world
       // void                    clearScene()


		void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


	private:
		static const float		PlayerSpeed;

        FontHolder               mFontHolder;
        TextureHolder            mTextureHolder;

		sf::RenderWindow&		mWindow;


		sf::Text                mScoreText;
		unsigned int            mScore;

		Flower                  mFlower; //world
		sf::Time                mFlowerGenTime;

        sf::Sprite              mWall;
        sf::String*             mMap;//world
        sf::IntRect             mWorldBounds;

		Cow&				    mCow; //world
		Cow*                    mAICows;

};

#endif // GAMESTATE_H
