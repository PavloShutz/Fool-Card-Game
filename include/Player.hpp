#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "Card.hpp"

class Player {
  std::string name{};

 protected:
  std::vector<Card> cards{};

 public:
  explicit Player(const std::string& name);
  virtual ~Player()                = default;

  Player(const Player&)            = delete;
  Player& operator=(const Player&) = delete;

  [[nodiscard]] std::string getName() const { return name; }

  void take(const Card card) { cards.push_back(card); }

  [[nodiscard]] Card getSmallestTrump(const Suit trump) const;

  [[nodiscard]] int  handSize() const { return static_cast<int>(cards.size()); }
  [[nodiscard]] bool hasCards() const { return !cards.empty(); }

  virtual void playEntryCards(
      std::vector<std::pair<std::optional<Card>, std::optional<Card>>>& table,
      Suit trump) = 0;

  [[nodiscard]] virtual bool beatCards(
      std::vector<std::pair<std::optional<Card>, std::optional<Card>>>& table,
      Suit trump) = 0;

  [[nodiscard]] virtual int addCards(
      std::vector<std::pair<std::optional<Card>, std::optional<Card>>>& table,
      Suit trump, int limit) = 0;
};

#endif