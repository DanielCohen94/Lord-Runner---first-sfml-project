#pragma once

#include "./Machine/State.h"
#include "macros.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <array>
#include <cmath>

class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(double dt);
	virtual bool handleEvent(const sf::Event& event);
	virtual void pause() {}
	virtual void start() {}

private:
	sf::Sprite mBackgroundSprite;
	sf::Sound m_soundState;
	sf::Sound m_sound;
	sf::Text m_title;
	std::vector< sf::Text > m_buttons;
	sf::Text m_textBack;

	bool m_backToMenu;
	bool m_pressed;

	bool m_avaibleMusicSelected;
	bool m_avaibleMusicPressed;

	bool m_no_avaibleMusicSelected;
	bool m_no_avaibleMusicPressed;

	bool m_showText;

	float mEffectTime;
	float mTextEffectTime;

	void centerOrigin(sf::Text&);
	void updateColorButton();
	void updateByMouse();
	void buildButtons(const sf::Vector2u&);
};