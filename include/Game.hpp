#pragma once

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "Card.hpp"
#include "Player.hpp"

namespace Core {
	constexpr std::size_t minNumberOfPlayers = 2, maxNumberOfPlayers = 6;

	class Game {
	public:
		Game(std::initializer_list<std::shared_ptr<Player>> newPlayers);
	
		void run();
	private:
		Pile deck;  // place to take cards from
		Pile table; // "battle area"
		Pile heap;  // "used" cards will be stored here

		std::vector<std::shared_ptr<Player>> players;
	};
} // namespace Core