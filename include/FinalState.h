#pragma once

#include "./Machine/State.h"
#include "macros.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>

class FinalState : public State
{
public:
	FinalState(StateStack& stack, Context context);
	~FinalState();

	virtual void draw();
	virtual bool update(double dt);
	virtual bool handleEvent(const sf::Event& event);

	virtual void pause() {}
	virtual void start() {}
private:
	sf::Sprite mBackgroundSprite;
	sf::Text m_title;
	sf::Text m_message;
	sf::Sound m_soundState;

	sf::String playerInput;
	sf::Text playerText;

	int m_score;
	int m_limit;

	std::string *m_score_player;
	std::string* m_name;

	double mElapsedTime;

	bool m_backToMenu;

	void centerOrigin(sf::Text&);
	bool inputLogic(int charTyped);
	void deleteLastChar();

};