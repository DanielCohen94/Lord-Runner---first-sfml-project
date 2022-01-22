#include "SettingsState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context), m_backToMenu(false), mEffectTime(0.0f),
	  m_showText(true), mTextEffectTime(0.0f)
{
	// booleans for buttons
	m_avaibleMusicSelected = false;
	m_avaibleMusicPressed = false;
	m_pressed = false;
	m_no_avaibleMusicSelected = false;
	m_no_avaibleMusicPressed = false;

	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::Menu).getSize();

	// get texture background
	sf::Texture& texture = context.textures->get(Textures::Menu);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x,
		(float)windowSize.y / textureSize.y);

	// build title
	sf::Font& font = context.fonts->get(Fonts::Main);
	m_title.setFont(font);
	m_title.setString("Settings");
	m_title.setFillColor(sf::Color(76, 0, 153));
	m_title.setCharacterSize(100);
	centerOrigin(m_title);
	m_title.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
	m_title.setOutlineColor(sf::Color::White);
	m_title.setOutlineThickness(5.f);

	// buttons
	buildButtons(windowSize);

	// footer message
	m_textBack.setFont(font);
	m_textBack.setString("Press enter to return to the menu");
	m_textBack.setFillColor(sf::Color(76, 0, 153));
	m_textBack.setCharacterSize(35);
	m_textBack.setOrigin(m_textBack.getLocalBounds().width / 2,
		m_textBack.getLocalBounds().height / 2);
	m_textBack.setPosition(sf::Vector2f(windowSize.x * 0.5f,
		(windowSize.y / 2) + (5 * 100)));
	m_textBack.setOutlineColor(sf::Color::White);
	m_textBack.setOutlineThickness(5.f);
	
	// sounds state
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);
	m_sound.setBuffer(context.sounds->get(SoundEffect::Button));
	m_sound.setPlayingOffset(sf::seconds(2.f));
	m_soundState.play();
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);

	window.draw(m_title);

	for (auto button : m_buttons)
		window.draw(button);

	if (m_showText)
		window.draw(m_textBack);

	window.draw(mousePicture);
}

bool SettingsState::update(double dt)
{
	if (m_pressed)
	{
		mEffectTime += (float)dt;
		updateColorButton();
		if (mEffectTime >= 1.0f)
		{
			// move to state after one second
			m_pressed = false;
			mEffectTime = 0.0f;
			if (m_avaibleMusicSelected || m_no_avaibleMusicSelected )
			{
				requestStackPop();
				requestStackPush(States::Menu);
			}
			else if (m_backToMenu)
			{
				m_soundState.stop();
				requestStackPop();
				requestStackPush(States::Menu);
			}
		}
	}

	// to display footer message by 0.5 seconds
	mTextEffectTime += (float)dt;
	if (mTextEffectTime >= 0.5f)
	{
		m_showText = !m_showText;
		mTextEffectTime = 0.0f;
	}

	this->updateCursor();

	this->updateByMouse();

	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	sf::RenderWindow& window = *getContext().window;
	InputManager* input = getContext().input;

	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_soundState.stop();
		requestStateClear();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_backToMenu = true;
		m_pressed = true;
	}

	if (event.MouseButtonPressed)
	{

		if (m_avaibleMusicPressed = input->isSpriteClicked(m_buttons[ButtonsSettings::AvailableMusic],
															sf::Mouse::Left, window))
		{
			m_avaibleMusicSelected = true;
			m_no_avaibleMusicSelected = false;
			m_pressed = true;
			getContext().playerInput->setUserSound(true);
			m_sound.play();
		}

		if (m_no_avaibleMusicPressed = input->isSpriteClicked(m_buttons[ButtonsSettings::NoAvailableMusic],
																sf::Mouse::Left, window))
		{
			m_no_avaibleMusicSelected = true;
			m_avaibleMusicSelected = false;
			m_pressed = true;
			getContext().playerInput->setUserSound(false);
			m_sound.play();
		}
		return true;
	}
	return false;
}

void SettingsState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

void SettingsState::buildButtons(const sf::Vector2u& windowSize)
{
	sf::Text text;
	text.setFont(getContext().fonts->get(Fonts::Main));
	text.setCharacterSize(55);
	text.setStyle(sf::Text::Bold);

	for (size_t i = 0; i < ButtonsSettings::Max; i++)
	{
		m_buttons.push_back(text);
		m_buttons[i].setFillColor(sf::Color::White);

		m_buttons[i].setOrigin(m_buttons[i].getLocalBounds().width / 2,
			m_buttons[i].getLocalBounds().height / 2);
		m_buttons[i].setPosition(sf::Vector2f(windowSize.x / 2.5,
			(windowSize.y / 2) + (i * 100)));
		m_buttons[i].setOutlineColor(sf::Color(76, 0, 153));
		m_buttons[i].setOutlineThickness(5.f);
	}

	m_buttons[ButtonsSettings::AvailableMusic].setString("Avaible Music");
	m_buttons[ButtonsSettings::NoAvailableMusic].setString("No Avaible Music");

}

void SettingsState::updateColorButton()
{
	if (m_avaibleMusicSelected)
	{
		m_buttons[ButtonsSettings::AvailableMusic].setFillColor(sf::Color::Black);
		m_buttons[ButtonsSettings::NoAvailableMusic].setFillColor(sf::Color::White);
	}
	else if (m_no_avaibleMusicSelected)
	{
		m_buttons[ButtonsSettings::AvailableMusic].setFillColor(sf::Color::White);
		m_buttons[ButtonsSettings::NoAvailableMusic].setFillColor(sf::Color::Black);
	}
}

void SettingsState::updateByMouse()
{
	auto mouse_pos = getContext().input->GetMousePosition(*getContext().window);
	auto translated_pos = getContext().window->mapPixelToCoords(mouse_pos);

	for ( auto &button : m_buttons)
	{
		// Rectangle-contains-point check
		if (button.getGlobalBounds().contains(translated_pos))
		{
			// Mouse is inside the sprite.
			button.setFillColor(sf::Color::Yellow);
		}
		else
			button.setFillColor(sf::Color::White);
	}
}
