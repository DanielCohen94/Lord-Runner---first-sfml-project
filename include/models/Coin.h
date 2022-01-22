#pragma once

#include "Trophy.h"

// forward declaration
class DynamicObject;

/* ================================================
class Coin
	As long as there is coin on the map
	the level continue
*/
class Coin : public Trophy
{
public:
	// Constractor / Distactor
	Coin(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~Coin();

	// public functions
	// virtual functions
	void virtual handleColision(DynamicObject& obj) override;
	void virtual handleColision(Player& obj) override;
	void resetExist() override; // new level

	// static function
	static const int getCount();  
	static const int getCollected();
	static void resetCollected();

private:
	static int m_num_coins; // all coin in the level
	static int m_num_collected; // coin that collected
}; // end coin