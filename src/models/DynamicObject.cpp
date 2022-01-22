#include "models/DynamicObject.h"

// Constractor / Distactor

/*/ Constractor :  
/*   position ,size and texture - send to Object constractor.
/*   speed , direction initialized here
/*/
DynamicObject::DynamicObject
(sf::Vector2f pos, sf::Vector2f size, size_t speed, sf::Texture* txt)
	: Object(pos, size , txt), m_moveSpeed(speed),m_dircetion(0)
{
	// that made dynamic Object can move betwwen two static Object
	this->m_rec->setScale(m_rec->getScale() * (float)0.8);
	m_first_position = this->m_rec->getPosition();
}

/* ===================================== *
 * ######### Public Functions ########## *
 * ===================================== */

 //===================================================
void DynamicObject::setDirectionDown()
{
	this->m_dircetion = Object_Direction::Down;
}

/* move function :
* get delta time and moving the character according to
* the direction it has and according to its speed*/
//===================================================
void DynamicObject::move(const float& dt)
{
	if(this->isExsist())
		this->m_rec->move
	(this->getMovement().x * this->m_moveSpeed * dt, this->getMovement().y * this->m_moveSpeed * dt);
}

//===================================================
void DynamicObject::goBack()
{
	this->m_rec->setPosition(getLastPos());
}

//===================================================
void DynamicObject::setFirstPos()
{
	this->m_rec->setPosition(getFirstPos());
}

//===================================================
const sf::Vector2f& DynamicObject::getPosition() const
{
	return this->m_rec->getPosition();
}

/* ######### Virual Functions ########## */

/* ===================================== *
 * ######### Private Functions ########## *
 * ===================================== */

// ############### Auxiliary Functions : ############ //

//===================================================
void DynamicObject::resetDirection()
{
	this->m_dircetion = 6;
}

//===================================================
void DynamicObject::SaveLastPosition()
{
	m_last_postion = this->getSprite().getPosition();
}

// ############### Get Functions : ############ //

// get movment vector by direction member
//===================================================
sf::Vector2f DynamicObject::getMovement() const
{
	switch (m_dircetion)
	{
	case 1:
		if (m_rec->getScale().x > 0 )
			this->m_rec->scale( -1, 1 );
		return (sf::Vector2f(-1.f, 0.f));
		break;
	case 2:
		if (m_rec->getScale().x < 0)
			this->m_rec->scale(-1, 1);
		return (sf::Vector2f(1.f, 0.f));
		break;
	case 3:
		return (sf::Vector2f(0.f, -1.f));
		break;
	case 4:
		return (sf::Vector2f(0.f, 1.f));
		break;
	default:
		return (sf::Vector2f(0.f, 0.f));
		break;
	}
}

//===================================================
const sf::Vector2f& DynamicObject::getLastPos() const
{
	return this->m_last_postion;
}

//===================================================
const sf::Vector2f& DynamicObject::getFirstPos() const
{
	return this->m_first_position;
}

