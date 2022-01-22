#include "models/MonsterRand.h"

// constructor
//===============================================================================
MonsterRand::MonsterRand(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Monster(pos, size, txt)
{

}

// update direction : random every 2 seconds
//===============================================================================
void MonsterRand::updateDirection(const float& dt)
{
	static float time = 4;

	time += dt;

	if (time > 2.f)
	{
		time = 0;
		m_dircetion = rand() % 4;
	}
	this->SaveLastPosition();
}
