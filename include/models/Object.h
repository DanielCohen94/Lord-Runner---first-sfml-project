#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// forward declaration
class StaticObject;
class DynamicObject;
class Monster;
class Player;
class Floor;
class Coin;
class Ladder;
class Ropes;
class Monster;


/* ================================================
Abstract class Object

Classes inherit directly : 1. StaticObject - absract class 
						   2. DynamicObject - absract class 
*/ 
class Object
{

public:
	// Constractor / Distactor
	Object(sf::Vector2f position, sf::Vector2f size, sf::Texture* txt); 
	virtual ~Object() ; 

	// public functions
	const sf::Sprite& getSprite() const;
	const bool collisionWith(const Object& obj) const;
	const bool isExsist() const;
	// virtual functions
	void virtual render(sf::RenderWindow* target);
	// Pure virtual functions 
	void virtual handleColision(Floor& obj) = 0;
	void virtual handleColision(Coin& obj) = 0 ;
	void virtual handleColision(Ladder& obj) = 0;
	void virtual handleColision(Ropes& obj) = 0;
	void virtual handleColision(Monster& obj) = 0;
	void virtual handleColision(DynamicObject& obj) = 0;

protected:
	sf::Sprite* m_rec;
	bool m_isExist;

private:

}; // end Object