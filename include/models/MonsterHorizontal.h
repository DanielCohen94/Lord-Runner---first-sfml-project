#pragma once

#include "Monster.h"
#include "../macros.h"

/* ================================================
class MonsterHorizontal

	Go right and left until you get stuck in the wall
*/
class MonsterHorizontal : public Monster
{

public:
	// Constractor / Distactor
	MonsterHorizontal(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~MonsterHorizontal() = default;
	// virtual functions
	void virtual updateDirection(const float& dt) override;

private:
	int m_horizional_dir;
}; // end MonsterHorizontal