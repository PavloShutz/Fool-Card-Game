#include "AI.hpp"

#include <ranges>

void AI::playEntryCards(
    std::vector<std::pair<std::optional<Card>, std::optional<Card> > > &table,
    const Suit trump) {
    Card min = cards.back();
    for (const auto &card: cards) {
        if (card.rank < min.rank ||
            (card.suit != trump && min.suit == trump)) {
            min = card;
        }
    }

    for (auto &card: cards) {
        if (card.rank == min.rank)
            table.emplace_back(card, std::nullopt);
    }

    while (true) {
        bool erased = false;
        for (int i = 0; i < cards.size(); ++i) {
            if (cards[i].rank == min.rank) {
                cards.erase(cards.begin() + i);
                erased = true;
                break;
            }
        }
        if (!erased) break;
    }
}

bool AI::beatCards(
    std::vector<std::pair<std::optional<Card>, std::optional<Card> > > &table,
    const Suit trump) {
    // sort table
    std::ranges::sort(table,
                      [trump](const auto &a, const auto &b) {
                          const bool aTrump = (a.first.value().suit == trump);
                          const bool bTrump = (b.first.value().suit == trump);
                          if (aTrump != bTrump) return bTrump;
                          return a.first.value().rank < b.first.value().rank;
                          // return canBeat(b.first.value(), a.first.value(), trump);
                      });
    // sort cards
    std::ranges::sort(cards,
                      [trump](const auto &a, const auto &b) {
                          const bool aTrump = (a.suit == trump);
                          const bool bTrump = (b.suit == trump);
                          if (aTrump != bTrump) return bTrump;
                          return a.rank < b.rank;
                      });
    // iterate over cards
    bool beaten = false;
    for (const auto &card: cards) {
        for (auto &[fst, snd]: table) {
            if (!snd.has_value() &&
                canBeat(card, fst.value(), trump)) {
                snd = card;
                beaten = true;
                break;
            }
        }
        if (!beaten) return false;
    }

    while (true) {
        bool erased = false;
        for (const auto &snd: table | std::views::values) {
            for (int i = 0; i < cards.size(); ++i) {
                if (snd.has_value() && cards[i] == snd) {
                    cards.erase(cards.begin() + i);
                    erased = true;
                    break;
                }
            }
        }
        if (!erased) break;
    }

    return true;
}

int AI::addCards(
    std::vector<std::pair<std::optional<Card>, std::optional<Card> > > &table,
    const Suit trump, const int limit) {
    int added = 0;

    for (const auto &[fst, snd]: table) {
        if (added >= limit) break;
        for (const auto &card: cards) {
            if (added >= limit) break;
            if (fst.has_value() && card.rank == fst->rank || snd.has_value() && card.rank == snd->rank) {
                table.emplace_back(card, std::nullopt);
                ++added;
            }
        }
    }

    while (true) {
        bool erased = false;
        for (const auto &[fst, snd]: table) {
            for (int i = 0; i < cards.size(); ++i) {
                if (fst.has_value() && cards[i] == fst || snd.has_value() && cards[i] == snd) {
                    cards.erase(cards.begin() + i);
                    erased = true;
                    break;
                }
            }
        }
        if (!erased) break;
    }

    return added;
}
