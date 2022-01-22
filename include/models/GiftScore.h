#pragma once

#include "../models/Gift.h"
/* ================================================
class GiftScore

	Adds to the player a Score
*/
class GiftScore: public Gift
{
public:

	// Constractor / Distactor
	GiftScore(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~GiftScore() = default;
	// virtual functions
	void virtual handleColision(DynamicObject& obj) override;
	void virtual handleColision(Player& obj) override;

private:

}; // end GiftScore