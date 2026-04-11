#include "Player.hpp"

Player::Player(const std::string& name) : name(name) { }

Card Player::getSmallestTrump(const Suit trump) const {
  Card smallest = cards.back();
  for (const auto& card : cards) {
    if (card.suit == trump && smallest.suit == trump &&
        card.rank < smallest.rank) {
      smallest = card;
    }
  }
  return smallest;
}
