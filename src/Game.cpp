#include "Game.hpp"

#include <algorithm>
#include <stdexcept>

using namespace Core;

std::random_device              Game::rd;
std::mt19937_64                 Game::g(rd());
std::uniform_int_distribution<> Game::dist(0, maxNumberOfPlayers - 1);

Game::Game(std::initializer_list<std::shared_ptr<Player>> newPlayers)
    : players(newPlayers) {
  if (players.size() < minNumberOfPlayers ||
      players.size() > maxNumberOfPlayers) {
    std::string msg = "Number of players is out of allowed range (from ";
    msg += std::to_string(minNumberOfPlayers);
    msg += " to ";
    msg += std::to_string(maxNumberOfPlayers);
    msg += " inclusively)";
    throw std::runtime_error(msg);
  }

  for (auto suit : suits)
    for (auto rank : ranks)
      deck.push_back(Card{rank, suit});
}

void Game::run() {
  running = true;

  shuffleDeck();
  dealCards();
  determineTrump();

  int defIdx = dist(g);

  while (running) {
    // 1. Each player can place card(s) on the table.
    // 2. The defending player must beat them or take cards,
    //    letting others to place additional cards, but not
    //    exceeding the limit of 6 (or 5 on the 1st turn) cards.
    // 3. Players take cards and the next defending player is chosen.
    bool placedAtLeastOnce = false;
    for (int i = -1; i < players.size() - 1; ++i) {
      if (i == 0)
        continue;

      if (players[defIdx + i]->place(table))
        placedAtLeastOnce = true;
    }

    if (players[defIdx]->beat(table))
      /* TODO: check if other players can place cards */;
    else
      /* TODO: take cards and replenish for other players */;
  }
}

void Game::shuffleDeck() { std::shuffle(deck.begin(), deck.end(), g); }

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
