#pragma once

#include "Trophy.h"
#include "Resources/ResourceIdentifiers.h"

// forward declaration
class DynamicObject;

/* ================================================
Abstract class Gift 

	father class of all types of gifts in the game
*/
class Gift : public Trophy
{
public:
	// Constractor / Distactor
	Gift(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	virtual ~Gift() = default;
	// virtual functions
	void virtual resetExist() override;
	// pure virtual functions
	void virtual handleColision(DynamicObject& obj) = 0;
	void virtual handleColision(Player& obj) = 0;

protected:

private:

};// end gift