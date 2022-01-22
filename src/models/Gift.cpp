#include "models\Gift.h"

// constructor
Gift::Gift(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt):
	Trophy(pos, size, txt)
{
}

//================================================================
void Gift::resetExist()
{
	// no reset gift if level start again
}

//================================================================
void Gift::handleColision(Player& obj)
{
	this->m_isExist = false;
}

