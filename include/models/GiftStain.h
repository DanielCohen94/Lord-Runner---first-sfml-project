#pragma once

#include "../models/Gift.h"
#include <SFML/System.hpp>

/* ================================================
class GiftStain

	put on screen stain to 3 seconds
*/
class GiftStain : public Gift
{
public:
	// Constractor / Distactor
	GiftStain(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~GiftStain() = default;
	// virtual functions
	void virtual handleColision(DynamicObject& obj) override;
	void virtual handleColision(Player& obj) override;
	// static function
	static bool isActive();

private:
	static bool m_is_active;
	static sf::Clock m_clock;
};