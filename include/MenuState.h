#pragma once

#include "./Machine/State.h"
#include "macros.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cmath>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(double dt);
	virtual bool handleEvent(const sf::Event& event);

    virtual void pause() {}
    virtual void start() {}

private:
	sf::Sprite mBackgroundSprite;
    sf::Text m_title;
	std::vector< sf::Text > m_buttons;

	sf::Sound m_sound;
	sf::Sound m_soundState;

    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;

    bool m_isSettingsButtonSelected;
    bool m_isSettingsButtonPressed;

    bool m_isRecordsSelected;
    bool m_isRecordsPressed;

    bool m_pressed = false;
    bool aload_music;
    float mEffectTime;

    void updateColorButton();
    void centerOrigin(sf::Text&);
    void updateByMouse();
    void buildButtons(const sf::Vector2u &);
};

