#include "RecordsState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RenderWindow.hpp>


RecordsState::RecordsState(StateStack& stack, Context context)
	: State(stack, context), m_backToMenu(false), mElapsedTime(0.0f)
	, m_showText(true), mTextEffectTime(0.0f)
{
	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::Menu).getSize();

	// get texture state
	sf::Texture& texture = context.textures->get(Textures::Scores);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x,
		(float)windowSize.y / textureSize.y);

	// get font state
	sf::Font& font = context.fonts->get(Fonts::Main);
	// title state
	m_title.setFont(font);
	m_title.setString("Hall of Fame");
	m_title.setFillColor(sf::Color::Black);
	m_title.setOutlineColor(sf::Color::Yellow);
	m_title.setOutlineThickness(4.f);
	m_title.setCharacterSize(100);
	centerOrigin(m_title);
	m_title.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y - 200);

	// get map scores
	m_multimap = context.playerInput->getSorted();
	// text to show from map scores
	m_userName = new sf::Text;
	m_userScore = new sf::Text;
	m_userName->setCharacterSize(50);
	m_userName->setColor(sf::Color::Yellow);
	m_userName->setOutlineColor(sf::Color::Black);
	m_userName->setOutlineThickness(4.f);
	m_userName->setFont(font);
	m_userName->setOrigin(m_userName->getLocalBounds().width / 2,
		m_userName->getLocalBounds().height / 2);
	m_userScore->setCharacterSize(50);
	m_userScore->setColor(sf::Color::Yellow);
	m_userScore->setOutlineColor(sf::Color::Black);
	m_userScore->setOutlineThickness(4.f);
	m_userScore->setFont(font);
	m_userScore->setOrigin(m_userScore->getLocalBounds().width / 2,
		m_userScore->getLocalBounds().height / 2);

	// message in footer state
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
	m_soundState.setBuffer(context.sounds->get(SoundEffect::TopScores));
	m_soundState.setLoop(true);
	m_soundState.play();
}

RecordsState::~RecordsState()
{
	delete m_userName;
	delete m_userScore;
	m_multimap.clear();
}

void RecordsState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	int i = 1;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);

	window.draw(m_title);

	window.draw(mousePicture);

	// Print the multimap 
	for (auto it : m_multimap)
	{
		str = it.first;
		score = it.second;
		m_userName->setString(str);
		
		m_userScore->setString(std::to_string(score));

		m_userName->setPosition(sf::Vector2f(window.getSize().x / 2.5 - 250,
			(window.getSize().y / 2) + (i * 100) - 200 ));

		m_userScore->setPosition(sf::Vector2f(window.getSize().x / 2.5 + 600,
			(window.getSize().y / 2) + (i * 100) - 200 ));

		window.draw(*m_userName);
		window.draw(*m_userScore);
		i++;
	}
	i = 0;

	if (m_showText)
		window.draw(m_textBack);
}

bool RecordsState::update(double dt)
{
	if (m_backToMenu)
	{
		m_backToMenu = false;
		m_soundState.stop();
		requestStackPop();
		requestStackPush(States::Menu);
	}

	// to footer message
	mTextEffectTime += (float)dt;
	if (mTextEffectTime >= 0.5f)
	{
		m_showText = !m_showText;
		mTextEffectTime = 0.0f;
	}

	this->updateCursor();

	return true;
}

bool RecordsState::handleEvent(const sf::Event& event)
{
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		requestStateClear();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		m_backToMenu = true;
	return true;
}

void RecordsState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}
