#pragma once

#include "./Machine/State.h"
#include "macros.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cmath>

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);
	~PauseState();

	virtual void draw();
	virtual bool update(double dt);
	virtual bool handleEvent(const sf::Event& event);

	virtual void pause() {}
	virtual void start() {}


private:
	sf::Sprite mBackgroundSprite;
	sf::Text mPausedText;
	std::vector<sf::Text> m_buttons;
	sf::Sound m_sound;
	sf::Sound m_soundState;
	sf::Clock m_clock;

	bool m_isBackMenuSelected;
	bool m_isBackMenuPressed;

	bool m_isResetGameSelected;
	bool m_isResetGamePressed;

	bool m_backToGameSelected;
	bool m_backToGamePressed;

	bool m_pressed;

	double mElapsedTime;

	void centerOrigin(sf::Text&);
	void updateColorButton();
	void updateByMouse();
	void buildButtons(const sf::Vector2f&);
};