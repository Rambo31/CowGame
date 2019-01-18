#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>


class Game : private sf::NonCopyable
{
	public:
								Game();
		void					run();


	private:
        void                    updateCowAnimation(sf::Time elapsedTime);

		void					processEvents();
		void					update(sf::Time elapsedTime);
		void					render();


		void					updateStatistics(sf::Time elapsedTime);
		void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


	private:
		static const float		PlayerSpeed;
		static const sf::Time	TimePerFrame;




		sf::RenderWindow		mWindow;
		sf::Texture				mTexture;
		sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;


		float                   curFrame;
		sf::Sprite				mPlayer;
		bool					mIsMovingUp;
		bool					mIsMovingDown;
		bool					mIsMovingRight;
		bool					mIsMovingLeft;
};

#endif // GAME_H
