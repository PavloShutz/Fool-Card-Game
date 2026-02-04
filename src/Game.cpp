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

  int defIdx    = dist(g);
  int refrained = 0;  // how many players refrained taking the move

  while (running) {
    switch (state) {
      case Attack : handleAttack(); break;
      case Defend : handleDefend(); break;
      case Result : handleResult(); break;
      case Cleanup: handleCleanup(); break;
      default     : break;
    }
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

void Game::handleAttack() { state = State::Defend; }

void Game::handleDefend() { }

void Game::handleResult() { }

void Game::handleCleanup() {
  if (checkWinCondition())
    running = false;
  state = State::Attack;
}

bool Game::checkWinCondition() const {
  if (!deck.empty())
    return false;

  int cnt = 0;  // number of active players
  for (const auto& player : players)
    if (player->cardsAmount() > 0)
      ++cnt;

  return cnt < 2;
}
