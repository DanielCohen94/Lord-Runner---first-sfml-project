#pragma once

#include "models/Monster.h"
#include "models/Player.h"
#include "models/Ladder.h"
#include "models/Ropes.h"
#include "../macros.h"
#include <vector>
#include "Ladder.h"
// strcut that using in bfs algorithm
struct NudeBfs {
public:
	int row;
	int col;
	std::vector<int> VecMov;

	NudeBfs(int x, int y, std::vector<int> w)
		: row(x), col(y), VecMov(w)
	{
	}
}; // end NudeBfs


/* ================================================
class MonsterSmart

	Walks smartly and seeks to get closer to the player.
	Uses the bfs algorithm
	gets in Constractor const Player.
	Build a mat of numbers by static objects
*/
class MonsterSmart : public Monster
{

public:
	// Constractor / Distactor
	MonsterSmart(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt,  Player* const p);
	~MonsterSmart() = default;
	// virtual functions
	void virtual setGrid(std::vector<std::vector<char>> &) override;
	void virtual updateDirection(const float& dt) override;
//	void virtual handleColision(Ladder& obj)override;
//	void virtual handleColision(Ropes& obj)override;

private:

	Player* m_copy_player;
	sf::Vector2f m_size;
	std::vector<std::vector<char>> m_map;
	std::vector<std::vector<int>> m_visited;
	size_t m_last_dir;
	sf::Vector2i m_last_cell;

	// private func
	sf::Vector2i getPosOnMat(DynamicObject*);
	size_t getDirectionSmartBfs(sf::Vector2i, sf::Vector2i);
	void buildVisited(const int);
	bool isInRange(int row, int col);

}; //end MonsterSmart