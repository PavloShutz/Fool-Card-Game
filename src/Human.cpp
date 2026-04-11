#include "Human.hpp"

void Human::playEntryCards(
    std::vector<std::pair<std::optional<Card>, std::optional<Card> > > &table,
    Suit trump) { }

bool Human::beatCards(
    std::vector<std::pair<std::optional<Card>, std::optional<Card> > > &table,
    Suit                                                                trump) {
  return false;
}

int Human::addCards(
    std::vector<std::pair<std::optional<Card>, std::optional<Card> > > &table,
    Suit trump, int limit) {
  return 0;
}
