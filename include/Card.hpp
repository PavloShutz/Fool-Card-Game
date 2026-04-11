#ifndef CARD_HPP
#define CARD_HPP

#include <string>

enum class Rank { Six = 6, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

enum class Suit { Diamonds, Hearts, Spades, Clubs };

struct Card {
  Rank rank;
  Suit suit;
};

inline bool operator==(const Card& a, const Card& b) {
  return (a.suit == b.suit) && (a.rank == b.rank);
}

inline std::string toString(Rank rank) {
  switch (rank) {
    case Rank::Six:
    case Rank::Seven:
    case Rank::Eight:
    case Rank::Nine:
    case Rank::Ten:
      return std::to_string(static_cast<int>(rank));
    case Rank::Jack:
      return "J";
    case Rank::Queen:
      return "Q";
    case Rank::King:
      return "K";
    case Rank::Ace:
      return "A";
    default:
      return "???";
  }
}

inline std::string toString(const Suit suit) {
  switch (suit) {
    case Suit::Diamonds:
      return "D";
    case Suit::Clubs:
      return "C";
    case Suit::Hearts:
      return "H";
    case Suit::Spades:
      return "S";
    default:
      return "???";
  }
}

inline std::string toString(const Card& card) {
  return toString(card.rank) + toString(card.suit);
}

inline bool canBeat(const Card& a, const Card& b, const Suit trump) {
  if ((a.suit != trump && b.suit != trump) ||
      (a.suit == trump && b.suit == trump)) {
    return (a.suit == b.suit) && (a.rank > b.rank);
      }
  return a.suit == trump;
}

#endif