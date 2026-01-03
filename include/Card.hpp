#pragma once

#include <vector>

namespace Core {
	enum class Suit {
		Hearts,
		Spades,
		Diamonds,
		Clubs,
		MAX_SUIT
	};

	enum class Rank {
		Six = 6,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King,
		Ace,
		MAX_RANK
	};

	static std::vector<Suit> suits = {
		Suit::Hearts,
		Suit::Spades,
		Suit::Diamonds,
		Suit::Clubs
	};

	static std::vector<Rank> ranks = {
		Rank::Six,
		Rank::Seven,
		Rank::Eight,
		Rank::Nine,
		Rank::Ten,
		Rank::Jack,
		Rank::Queen,
		Rank::King,
		Rank::Ace
	};

	struct Card {
		Rank rank = Rank::MAX_RANK;
		Suit suit = Suit::MAX_SUIT;
	};

	using Pile = std::vector<Card>;

	// TODO: Document this
	inline bool comp(const Card& card1, const Card& card2, Suit trump) {
		if ((card1.suit != trump && card2.suit != trump)
			|| (card1.suit == trump && card2.suit == trump)) {
			return (card1.suit == card2.suit) && (card1.rank > card2.rank);
		}
		return card1.suit == trump;
	}
}