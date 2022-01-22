#include "PlayerInput.h"

PlayerInput::PlayerInput()
{
	this->m_score = 0;
	this->m_userSound = true;
}

PlayerInput::~PlayerInput()
{

}

void PlayerInput::setScore(const int& sc)
{
	this->m_score = sc;
}

void PlayerInput::setSuccess(const bool& scs)
{
	this->m_success = scs;
}

int PlayerInput::getScore() const
{
	return this->m_score;
}
bool PlayerInput::getSuccess() const
{
	return this->m_success;
}

void PlayerInput::updateScore(std::string nameUser, const int& score)
{
	this->m_scores.insert(std::make_pair(score, nameUser));

    // printBySort();
}

std::multimap<std::string, int>& PlayerInput::getSorted()
{
    for (auto& it : m_scores)
    {
        m_multimap.insert({ it.second, it.first });
    }

    return this->m_multimap;
}

void PlayerInput::setUserSound(const bool& sound)
{
    this->m_userSound = sound;
}

bool PlayerInput::getUserSound() const
{
    return this->m_userSound;
}

void PlayerInput::printBySort(sf::RenderWindow* window)
{
    sf::Text userName;
    sf::Text userScore;
    // Declare a multimap 
    std::multimap<std::string, int> MM;
    int i = 0;
    std::string str;
    int score;

    // Insert every (key-value) pairs from 
    // map M to multimap MM as (value-key) 
    // pairs 
    for (auto& it : m_scores)
	{
        MM.insert({ it.second, it.first });
    }

    userName.setCharacterSize(50);
    userName.setColor(sf::Color::Green);
    userScore.setCharacterSize(50);
    userScore.setColor(sf::Color::Green);

    // Print the multimap 
    for (auto& it : MM)
    {
        str = it.first;
        score = it.second;
        userName.setString(str);
        userScore.setString(std::to_string(score));

        userName.setPosition(5 * i, 100);
        userScore.setPosition(5 * i, 500);

        window->draw(userName);
        window->draw(userScore);
        i++;
    }
}