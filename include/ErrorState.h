#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>


class ErrorState : public State
{
public:
	ErrorState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(double dt);
	virtual bool handleEvent(const sf::Event& event);

	virtual void pause() {}
	virtual void start() {}
private:
	sf::Sprite mBackgroundSprite;
	sf::Sound m_soundState;
	sf::Text m_title;

	bool m_backToMenu;
	float mElapsedTime;

	void centerOrigin(sf::Text&);
};