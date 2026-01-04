#include <stdexcept>

#include "Game.hpp"

using namespace Core;

Game::Game(std::initializer_list<std::shared_ptr<Player>> newPlayers)
	: players(newPlayers)
{
	if (players.size() < minNumberOfPlayers || players.size() > maxNumberOfPlayers) {
		throw std::exception("Number of players is out of allowed range.");
	}
		
	for (int i = 0; i < ranks.size(); ++i)
		for (int j = 0; j < suits.size(); ++j)
			deck.push_back(Card{ ranks[i], suits[j] });
}

void Game::run()
{
	// TODO
}
