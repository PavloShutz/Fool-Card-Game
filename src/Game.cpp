#include <algorithm>
#include <stdexcept>

#include "Game.hpp"

using namespace Core;

std::random_device Game::rd;
std::mt19937_64 Game::g(rd());

Game::Game(std::initializer_list<std::shared_ptr<Player>> newPlayers)
	: players(newPlayers)
{
	if (players.size() < minNumberOfPlayers || players.size() > maxNumberOfPlayers) {
		std::string msg = "Number of players is out of allowed range (from ";
		msg += std::to_string(minNumberOfPlayers);
		msg += " to ";
		msg += std::to_string(maxNumberOfPlayers);
		msg += " inclusively)";
		throw std::runtime_error(msg);
	}

	for (auto suit : suits)
		for (auto rank : ranks)
			deck.push_back(Card{ rank, suit });
}

void Game::run() {
	running = true;

	shuffleDeck();
	dealCards();
	determineTrump();

	while (running) {

	}
}

void Game::shuffleDeck() {
	std::shuffle(deck.begin(), deck.end(), g);
}

void Game::dealCards() {
	for (int i = 0; i < 6; ++i) {
		for (auto& player : players) {
			player->take(deck.back());
			deck.pop_back();
		}
	}
}

void Game::determineTrump() {
	trump = deck.back().suit;
	std::swap(deck.front(), deck.back());
}
