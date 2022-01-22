#include "models/Player.h"
#include <Windows.h>
#include <chrono>
#include <thread>

#include "./Resources/ResourceHolder.h"
#include "models/Floor.h"

// constructor
Player::Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt, SoundBufferHolder& sounds) :
	DynamicObject(pos, size, SPEED_PLAYER,txt),
	m_is_injured(false), m_life(INIT_LIFE), m_score(INIT),m_numLevel(1), m_direction_dig(INIT)

{
	m_soundGetCoin.setBuffer(sounds.get(SoundEffect::PlayerCoin));
	m_soundGetCoin.setVolume(30.0f);
	m_soundInjured.setBuffer(sounds.get(SoundEffect::PlayerDead));
	m_soundInjured.setVolume(30.0f);
	m_soundLifeUp.setBuffer(sounds.get(SoundEffect::LifeUp));
	m_soundLifeUp.setVolume(30.0f);
	m_soundScoreUp.setBuffer(sounds.get(SoundEffect::ScoreUp));
	m_soundScoreUp.setVolume(30.0f);
	m_soundStain.setBuffer(sounds.get(SoundEffect::Stain));
	m_soundStain.setVolume(30.0f);
	m_soundAddMon.setBuffer(sounds.get(SoundEffect::AddMonster));
	m_soundAddTime.setBuffer(sounds.get(SoundEffect::AddTime));
}

/*
	new Data : 
	at each new stage initializes the
	position and size of the player
*/
//=============================================================
void Player::newData(sf::Vector2f pos, sf::Vector2f avgPix)
{
	m_rec->setScale(
		(avgPix.x / (m_rec->getTexture()->getSize().x)),
		(avgPix.y / (m_rec->getTexture()->getSize().y)));
	this->m_rec->setScale(m_rec->getScale() * (float)0.8);
	//m_rec->setOrigin(avgPix.x / 2.f, avgPix.y / 2.f);
	m_rec->setPosition(sf::Vector2f((pos.x * avgPix.x + avgPix.x / 2u),
		((pos.y * avgPix.y) + avgPix.y / 2u)));
	//(sf::Vector2f((pos.x * avgPix.x) + avgPix.x / 2u, (pos.y * avgPix.y) + avgPix.y / 2u));

	this->m_first_position = m_rec->getPosition();
	//this->m_numLevel++;
	this->m_score += (m_numLevel - 1) * AddCoins::NewLevel;

}

/*
	update Direction :
	By pressing the arrow keys
*/
//=============================================================
void Player::updateDirection(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_dircetion = Object_Direction::Left;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_dircetion = Object_Direction::Right;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_dircetion = Object_Direction::Up;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_dircetion = Object_Direction::Down;

	this->SaveLastPosition();
}

/*
	dig :
	update direction of dig
	and reutrn true if x or z pressed
*/
//=============================================================
bool Player::dig()
{
	sf::Vector2f vec2f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->m_direction_dig = Object_Direction::Left;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		this->m_direction_dig = Object_Direction::Right;
		return true;
	}
	return false;
}

/*
	return vector of position to dig
*/
//=============================================================
sf::Vector2f Player::getMovementDig(sf::Vector2f size) const
{
	switch (m_direction_dig)
	{
	case 1:
		return (sf::Vector2f(this->m_rec->getPosition().x - ((float)1 * (size.x )),
			this->m_rec->getPosition().y + (float)1 * size.y ));
	case 2:
		return (sf::Vector2f(this->m_rec->getPosition().x + ((float)1 * (size.x )),
			this->m_rec->getPosition().y + (float)1 * size.y ));
	default:
		return (sf::Vector2f(0.f, 0.f));
	}
}

// ============ handle Colision functions: ====================

//=============================================================
void Player::handleColision(Floor& obj)
{
	if (obj.isExsist())
		this->goBack();
	// if go sown to floor that duul with monster
	else if (obj.isFull())
		this->injured();
}

//=============================================================
void Player::handleColision(Coin& obj)
{
	if (obj.isExsist())
	{
		obj.handleColision(*this);
		m_soundGetCoin.play();
		this->m_score += m_numLevel * AddCoins::MeetCoin;
	}
}

//=============================================================
void Player::handleColision(Monster& obj)
{
	if(!m_is_injured && obj.isExsist())
		this->injured();
}

//=============================================================
void Player::handleColision(GiftLife& obj)
{
	if (obj.isExsist())
	{
		obj.handleColision(*this);
		m_soundLifeUp.play();
		if(m_life < MAX_LIFE)
			this->m_life++;
	}
}

//=============================================================
void Player::handleColision(GiftScore& obj)
{
	if (obj.isExsist())
	{
		obj.handleColision(*this);
		m_soundScoreUp.play();
		this->m_score += AddCoins::MeetGift;
	}
}

//=============================================================
void Player::handleColision(GiftMonster& obj)
{
	if (obj.isExsist())
	{
		m_soundAddMon.play();
		obj.handleColision(*this);
	}
}

//=============================================================
void Player::handleColision(GiftStain& obj)
{
	if (obj.isExsist())
	{
		m_soundStain.play();
		obj.handleColision(*this);
	}
}

//=============================================================
void Player::handleColision(GiftTime& obj)
{
	if (obj.isExsist())
	{
		m_soundAddTime.play();
		obj.handleColision(*this);
	}
}

//=============================================================
void Player::newLevel() 
{
	m_numLevel++;
}

// injured the player
//=============================================================
void Player::injured() 
{
	m_life--;
	m_soundInjured.play();
	m_is_injured = true;
	Coin::resetCollected();
}

//=============================================================
const int Player::getLife() const
{
	return m_life;
}

//=============================================================
void Player::resetData()
{
	this->resetDirection();
}

// ====================== get functions: ======================

//=============================================================
const bool Player::isInjured()
{
	if (m_is_injured)
	{
		m_is_injured = false;
		return true;
	}
	return false;
}

//=============================================================
const int Player::getScore() const
{
	return m_score;
}

//=============================================================
const int Player::getLevel() const
{
	return m_numLevel;
}
