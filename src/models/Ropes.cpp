#include "models/Ropes.h"

//constructor
//=============================================================
Ropes::Ropes(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{
	// that made ropes skinny
	this->m_rec->setScale(m_rec->getScale().x * (float)1, m_rec->getScale().y * (float)0.5);
}

//=============================================================
void Ropes::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

// stand only on the top of the ropes
//=============================================================
bool Ropes::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	/*if ((this->m_rec->getPosition().x + size.x / 2 >= obj.getSprite().getPosition().x
		&& this->m_rec->getPosition().x - size.x / 2 <= obj.getSprite().getPosition().x)
		&& ( this->m_rec->getPosition().y + size.y / 2 - 5 <= obj.getSprite().getPosition().y
		&& this->m_rec->getPosition().y + size.y / 2 >= obj.getSprite().getPosition().y  )
		)*/

		if ((this->m_rec->getPosition().x + size.x / 2 >= obj.getSprite().getPosition().x
			&& this->m_rec->getPosition().x - size.x / 2 <= obj.getSprite().getPosition().x)
			&& (this->m_rec->getPosition().y + size.y / 2 - 5 <= obj.getSprite().getPosition().y
				&& this->m_rec->getPosition().y + size.y >= obj.getSprite().getPosition().y)
			)
			return true;
	return false;
}
