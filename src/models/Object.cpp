#include "models/Object.h"

// contructor
Object::Object(sf::Vector2f position, sf::Vector2f size, sf::Texture* txt)
	: m_isExist(true)
{
	m_rec = new sf::Sprite;

	m_rec->setTexture(*txt);
	
	// set size by average cell
	m_rec->setScale(sf::Vector2f(size.x / txt->getSize().x,
		size.y / txt->getSize().y));

	m_rec->setOrigin(sf::Vector2f(txt->getSize() / 2u));

	m_rec->setPosition
	(sf::Vector2f((position.x * size.x) + size.x / 2u,
		(position.y * size.y) + size.y / 2u));
}

// distructor
Object::~Object()
{
	delete this->m_rec;
}

//=======================================================
const sf::Sprite& Object::getSprite() const
{
	return *this->m_rec;
}

//=======================================================
const bool Object::collisionWith(const Object& obj) const
{
	return m_rec->getGlobalBounds().intersects(obj.m_rec->getGlobalBounds());
}

//=======================================================
const bool Object::isExsist() const
{
	return m_isExist;
}

//=======================================================
void Object::render(sf::RenderWindow* window) 
{
	window->draw(*m_rec);
}




