//
// Created by User on 11.04.2026.
//

#include "GameLap.hpp"

#include <algorithm>
#include <iostream>

GameLap::GameLap(State *state, std::vector<std::unique_ptr<Player> > players)
    : state(state) {
  context.players = std::move(players);
  state->setGameLap(this);
}

void GameLap::initDeck() {
  for (int i = static_cast<int>(Rank::Six); i <= static_cast<int>(Rank::Ace);
       ++i) {
    for (int j = 0; j < 4; ++j) {
      context.deck.push_back(
          {.rank = static_cast<Rank>(i), .suit = static_cast<Suit>(j)});
    }
  }
}

void GameLap::transitionToState(State *newState) {
  if (!newState)
    return;

  delete state;
  state = newState;
  state->setGameLap(this);
}

void StartState::execute() {
  auto       &deck    = gameLap->context.deck;
  const auto &players = gameLap->context.players;

  std::ranges::shuffle(deck, g);

  for (int i = 0; i < 6; ++i) {
    for (auto &&ptr : players) {
      ptr->take(deck.back());
      deck.pop_back();
    }
  }

  auto &trump = gameLap->context.trump;
  trump       = deck.back().suit;
  std::swap(deck.back(), deck.front());

  Card smallest = players.back()->getSmallestTrump(trump);
  for (int i = 0; i < players.size(); ++i) {
    if (const Card temp = players[i]->getSmallestTrump(trump);
        temp.rank < smallest.rank) {
      smallest                        = temp;
      gameLap->context.entryPlayerIdx = i;
    }
  }
  gameLap->context.defencePlayerIdx =
      static_cast<int>((gameLap->context.entryPlayerIdx + 1) % players.size());

  gameLap->transitionToState(new EntryState);
}

void EntryState::execute() {
  const auto &players        = gameLap->context.players;
  const auto &entryPlayerIdx = gameLap->context.entryPlayerIdx;
  players[entryPlayerIdx]->playEntryCards(gameLap->context.table,
                                          gameLap->context.trump);
  std::cout << players[entryPlayerIdx]->getName() << " made an entry move\n";

  gameLap->transitionToState(new DefenceState);
}

void DefenceState::execute() {
  const auto &players          = gameLap->context.players;
  const auto &defencePlayerIdx = gameLap->context.entryPlayerIdx;
  auto       &beaten           = gameLap->context.beaten;
  beaten = players[defencePlayerIdx]->beatCards(gameLap->context.table,
                                                gameLap->context.trump);
  std::cout << players[defencePlayerIdx]->getName() << " has"
            << (beaten ? " " : " not ") << "managed to beat cards\n";

  gameLap->transitionToState(new AddState);
}

void AddState::execute() {
  const auto &players          = gameLap->context.players;
  const auto &defencePlayerIdx = gameLap->context.entryPlayerIdx;
  const auto &entryPlayerIdx   = gameLap->context.entryPlayerIdx;

  int  limit                   = std::min(players[defencePlayerIdx]->handSize(),
                       gameLap->context.firstMove ? 5 : 6);
  bool addedCards              = false;
  for (int i = 0; i < players.size(); ++i) {
    const int current = static_cast<int>((i + entryPlayerIdx) % players.size());
    if (current == defencePlayerIdx)
      continue;
    const int added = players[current]->addCards(gameLap->context.table,
                                                 gameLap->context.trump, limit);
    limit -= added;
    if (limit <= 0)
      break;
    if (added > 0) {
      addedCards = true;
      std::cout << players[current]->getName() << " has added " << added
                << " cards\n";
    }
  }

  if (gameLap->context.beaten && addedCards)
    gameLap->transitionToState(new DefenceState);
  else
    gameLap->transitionToState(new ConcludeState);
}

void ConcludeState::execute() {
  auto       &players          = gameLap->context.players;
  auto       &eliminated       = gameLap->context.eliminated;
  auto       &defencePlayerIdx = gameLap->context.defencePlayerIdx;
  auto       &entryPlayerIdx   = gameLap->context.entryPlayerIdx;
  auto       &deck             = gameLap->context.deck;
  auto       &heap             = gameLap->context.heap;
  auto       &table            = gameLap->context.table;
  const auto &beaten           = gameLap->context.beaten;

  gameLap->context.firstMove   = false;
  for (int i = 0; i < players.size(); ++i) {
    if (deck.empty())
      break;
    const auto &current =
        players[static_cast<int>((i + entryPlayerIdx) % players.size())];
    if (current == players[defencePlayerIdx])
      continue;
    for (int j = current->handSize(); j < 6; ++j) {
      if (!deck.empty()) {
        current->take(deck.back());
        deck.pop_back();
      }
    }
  }

  if (beaten) {
    for (int i = players[defencePlayerIdx]->handSize(); i < 6; ++i) {
      if (!deck.empty()) {
        players[defencePlayerIdx]->take(deck.back());
        deck.pop_back();
      }
    }

    for (auto &[fst, snd] : table) {
      if (fst.has_value())
        heap.push_back(fst.value());
      if (snd.has_value())
        heap.push_back(snd.value());
    }
  } else {
    for (auto &[fst, snd] : table) {
      if (fst.has_value())
        players[defencePlayerIdx]->take(fst.value());
      if (snd.has_value())
        players[defencePlayerIdx]->take(snd.value());
    }
  }

  table.clear();

  int nextEntryIdx =
      static_cast<int>((defencePlayerIdx + (beaten ? 0 : 1)) % players.size());

  for (auto it = players.begin(); it != players.end();) {
    if (!(*it)->hasCards()) {
      const int removedIdx =
          static_cast<int>(std::distance(players.begin(), it));

      eliminated.push_back(std::move(*it));
      it = players.erase(it);

      if (removedIdx < nextEntryIdx) {
        --nextEntryIdx;
      }
    } else {
      ++it;
    }
  }

  if (players.size() > 1) {
    entryPlayerIdx   = nextEntryIdx;  //% players.size());
    defencePlayerIdx = static_cast<int>((entryPlayerIdx + 1) % players.size());
    gameLap->transitionToState(new EntryState);
  } else {
    gameLap->transitionToState(new ExitState);
  }
}

void ExitState::execute() {
  std::cout << gameLap->context.players[0]->getName() << " is a fool!\n";
  std::cout << "Game over!\n";
  gameLap->context.lapIsOver = true;
}