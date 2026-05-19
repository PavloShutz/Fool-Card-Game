#include "Player.hpp"

#include <algorithm>
#include <tuple>

Player::Player(const std::string& name) : name(name) { }

Card Player::getWeakestTrump(const Suit trump) const {
  // 1. Try to find the weakest trump
  // 2. Otherwise, use Player::getWeakestTrump to find the strongest
  // non-trump card.
  Card smallest   = cards.back();
  bool foundTrump = false;
  for (const auto& card : cards) {
    if (card.suit == trump) {
      if (!foundTrump || card.rank < smallest.rank) {
        smallest   = card;
        foundTrump = true;
      }
    }
  }
  return smallest;
}

Card Player::getWeakestCard(const Suit trump) const {
  return *std::ranges::min_element(cards, [=](const Card& a, const Card& b) {
    return std::make_tuple(a.suit == trump, a.rank) <
           std::make_tuple(b.suit == trump, b.rank);
  });
}