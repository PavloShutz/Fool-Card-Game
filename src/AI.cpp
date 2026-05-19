#include "AI.hpp"

#include <algorithm>
#include <ranges>

namespace {
using Table =
    std::vector<std::pair<std::optional<Card>, std::optional<Card>>>;

auto cardLess(const Suit trump) {
  return [trump](const Card& a, const Card& b) {
    const bool aTrump = (a.suit == trump);
    const bool bTrump = (b.suit == trump);
    if (aTrump != bTrump)
      return bTrump;
    return a.rank < b.rank;
  };
}

std::vector<Rank> collectTableRanks(const Table& table) {
  std::vector<Rank> ranks;
  ranks.reserve(table.size() * 2);
  for (const auto& [fst, snd] : table) {
    if (fst)
      ranks.push_back(fst->rank);
    if (snd)
      ranks.push_back(snd->rank);
  }
  return ranks;
}
}  // namespace

void AI::playEntryCards(
    std::vector<std::pair<std::optional<Card>, std::optional<Card> > > &table,
    const Suit                                                          trump) {
  const Rank rankToPlay = getWeakestCard(trump).rank;

  for (const auto& card : cards) {
    if (card.rank == rankToPlay)
      table.emplace_back(card, std::nullopt);
  }

  std::erase_if(cards, [rankToPlay](const Card& card) {
    return card.rank == rankToPlay;
  });
}

bool AI::beatCards(
    std::vector<std::pair<std::optional<Card>, std::optional<Card> > > &table,
    const Suit                                                          trump) {
  const auto less = cardLess(trump);
  std::ranges::sort(table, [less](const auto& a, const auto& b) {
    return less(a.first.value(), b.first.value());
  });
  std::ranges::sort(cards, less);

  for (auto& [fst, snd] : table) {
    if (snd.has_value())
      continue;
    const Card& attack = fst.value();
    const auto  it =
        std::ranges::find_if(cards, [&](const Card& card) {
          return canBeat(card, attack, trump);
        });
    if (it == cards.end())
      return false;
    snd = *it;
    cards.erase(it);
  }

  return true;
}

int AI::addCards(
    std::vector<std::pair<std::optional<Card>, std::optional<Card> > > &table,
    const Suit trump, const int limit) {
  const auto ranks = collectTableRanks(table);
  const auto rankMatches = [&](const Rank rank) {
    return std::ranges::find(ranks, rank) != ranks.end();
  };

  int added = 0;
  for (auto it = cards.begin(); it != cards.end() && added < limit;) {
    if (rankMatches(it->rank)) {
      table.emplace_back(*it, std::nullopt);
      it = cards.erase(it);
      ++added;
    } else {
      ++it;
    }
  }

  return added;
}
