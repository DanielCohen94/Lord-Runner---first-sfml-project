#pragma once

#include "models/Monster.h"

/* ================================================
class MonsterRand 

	Go random between 4 direction
*/
class MonsterRand : public Monster
{

public:

	// Constractor / Distactor
	MonsterRand(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~MonsterRand() = default;
	// virtual functions
	void virtual updateDirection(const float& dt) override;

private:

}; // end MonsterRand 