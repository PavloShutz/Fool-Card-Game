//
// Created by User on 11.04.2026.
//

#ifndef GAMELAP_HPP
#define GAMELAP_HPP

#include <vector>
#include <optional>
#include <memory>
#include <random>

#include "Card.hpp"
#include "Player.hpp"

static std::random_device rd;
static std::mt19937 g{rd()};

struct GameContext {
  using Table = std::vector<std::pair<std::optional<Card>, std::optional<Card> > >;

  std::vector<Card> deck;
  std::vector<Card> heap;
  Table table;

  std::vector<std::unique_ptr<Player> > players;
  std::vector<std::unique_ptr<Player> > eliminated;

  Suit trump{Suit::Clubs};
  bool firstMove{false};
  bool beaten{false};
  bool lapIsOver{false};

  int entryPlayerIdx{0};
  int defencePlayerIdx{0};
};

class State {
protected:
  class GameLap *gameLap{nullptr};

public:
  State() = default;

  virtual ~State() = default;

  State &operator=(const State &) = delete;

  State(const State &) = delete;

  void setGameLap(GameLap *object) {
    gameLap = object;
  }

  virtual void execute() = 0;
};

class GameLap {
  std::unique_ptr<State> state;

public:
  GameContext context;

  GameLap() = default;
  explicit GameLap(State *state, std::vector<std::unique_ptr<Player> > players);

  ~GameLap() = default;
  
  void initContext() {
    initDeck();
  }

  void transitionToState(State *newState);


  void executeTurn() const {
    while (!context.lapIsOver)
      state->execute();
  }

private:
  void initDeck();
};

class StartState : public State {
public:
  void execute() override;
};

class EntryState : public State {
public:
  void execute() override;
};

class DefenceState : public State {
public:
  void execute() override;
};

class AddState : public State {
public:
  void execute() override;
};

class ConcludeState : public State {
public:
  void execute() override;
};

class ExitState : public State {
public:
  void execute() override;
};

#endif
