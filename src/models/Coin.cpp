#include "models/Coin.h"

// static definition
int Coin::m_num_coins = 0;
int Coin::m_num_collected = 0;

/* constructor 

Each coin that build ,raises the counter
=================================*/
Coin::Coin(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Trophy(pos, size, txt)
{
	++m_num_coins;
}

// distructor
Coin::~Coin()
{
	--m_num_coins;
}

// get functions :
//===================================================
const int Coin::getCount()
{
	return m_num_coins;
}

//===================================================
const int Coin::getCollected()
{
	return m_num_collected;
}

// reset function:
//===================================================
void Coin::resetCollected()
{
	m_num_collected = 0;
}

//===================================================
void Coin::resetExist()
{
	this->m_isExist = true;
}

// handle colision functions:
//===================================================
void Coin::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

//===================================================
void Coin::handleColision(Player& obj)
{
	this->m_isExist = false;
	this->m_num_collected++;
}
