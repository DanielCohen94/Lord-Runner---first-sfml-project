#pragma once

#include "./Machine/State.h"
#include "macros.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cmath>

class GetReadyState : public State
{
public:
	GetReadyState(StateStack& stack, Context context);
	~GetReadyState();

	virtual void		draw();
	virtual bool		update(double dt);
	virtual bool		handleEvent(const sf::Event& event);

	virtual void pause() {}
	virtual void start() {}


private:
	sf::Text m_counter;
	sf::Text m_titleReady;

	sf::Sprite mBackgroundSprite;
	sf::Sound m_soundState;
	sf::Clock m_clock;
	static int init;

	int m_counterdown;
	float m_time;

	void centerOrigin(sf::Text&);

	double mCounterTime;
};