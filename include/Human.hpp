#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "Player.hpp"

class Human : public Player {
public:
  using Player::Player;

  void playEntryCards(
      std::vector<std::pair<std::optional<Card>, std::optional<Card>>>& table,
      Suit trump) override;

  bool beatCards(
      std::vector<std::pair<std::optional<Card>, std::optional<Card>>>& table,
      Suit trump) override;

  int addCards(
      std::vector<std::pair<std::optional<Card>, std::optional<Card>>>& table,
      Suit trump, int limit) override;
};

#endif