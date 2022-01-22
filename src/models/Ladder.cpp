#include "models/Ladder.h"

// constructor
Ladder::Ladder(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{
	// made ladder Tall and narrow
	this->m_rec->setScale(m_rec->getScale().x * (float)0.5,
		m_rec->getScale().y * (float)2.15);
}

//========================================================================
void Ladder::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

// do you stand on laddder
//========================================================================
bool Ladder::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	return this->collisionWith(obj);
}
