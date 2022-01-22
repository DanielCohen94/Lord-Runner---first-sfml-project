#include "ContainerStatus.h"

ContainerStatus::ContainerStatus(sf::Texture* txt, sf::Font* fnt)
{
	this->m_heart.setTexture(*txt);
	m_heart.setScale((float)0.15, (float)0.15);
	m_heart.setPosition(0, ROW + 50);

	this->m_textLevel.setFont(*fnt);
	m_textLevel.setPosition(600, ROW + 50 );
	m_textLevel.setFillColor(sf::Color::White);
	m_textLevel.setScale(1.5, 1.5);


	this->m_textScore.setFont(*fnt);
	m_textScore.setPosition(1000, ROW + 50);
	m_textScore.setFillColor(sf::Color::White);
	m_textScore.setScale(1.5, 1.5);
	
	this->m_textTime.setFont(*fnt);
	m_textTime.setPosition(1350, ROW + 50);
	m_textTime.setFillColor(sf::Color::White);
	m_textTime.setScale(1.5, 1.5);
}

ContainerStatus::~ContainerStatus()
{

}

void ContainerStatus::renderStatus
(Player& p, sf::RenderWindow* window, bool is_on_time, float t_in_s)
{
	m_textScore.setString("Score : " + std::to_string(p.getScore()));
	m_textLevel.setString("Level : " + std::to_string(p.getLevel()));


	for (int i = 0; i < p.getLife();i++)
	{
		m_heart.setPosition((float)i * 100, (float)ROW + 50);
		window->draw(m_heart);
	}

	window->draw(m_textScore);
	window->draw(m_textLevel);

	if (is_on_time)
	{
		(t_in_s < 6 && ((int)t_in_s % 2 == 0)) ? this->m_textTime.setFillColor(sf::Color::Red)
			: this->m_textTime.setFillColor(sf::Color::White);

		if(t_in_s > 0.2 )
			this->m_textTime.setString("Time: " + std::to_string(t_in_s));
		else
			this->m_textTime.setString("Time: " + std::to_string(0.0f));


		window->draw(m_textTime);
	}
}
