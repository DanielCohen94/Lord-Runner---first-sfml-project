#pragma once

#include <iostream>
#include <sstream>
#include <map>
#include <SFML/Graphics.hpp>

class PlayerInput
{
public:
	PlayerInput();
	~PlayerInput();

	void setScore(const int&);
	void setSuccess(const bool&);
	void setUserSound(const bool&);

	int getScore() const;
	bool getSuccess() const;
	bool getUserSound() const;

	void updateScore(std::string nameUser, const int& score);

	void printBySort(sf::RenderWindow* window);

	std::multimap<std::string, int>& getSorted();

private:
	bool m_success;
	int m_score;
	sf::String m_playerInput;
	sf::Text m_playerText;

	// TODO -> settings state
	bool m_userSound;

	std::map<int, std::string> m_scores;
	std::multimap<std::string, int> m_multimap;
};