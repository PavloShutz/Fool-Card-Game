#include "Game.hpp"

using namespace Core;

Game::Game(std::initializer_list<std::shared_ptr<Player>> newPlayers)
	: players(newPlayers)
{
	for (int i = 0; i < ranks.size(); ++i)
		for (int j = 0; j < suits.size(); ++j)
			deck.push_back(Card{ ranks[i], suits[j] });
}