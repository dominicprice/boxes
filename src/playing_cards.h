#pragma once

/*
Brief description:
	This header file contains classes and auxillary functions to provide
	an OO model of a deck of cards.
	Deck class:
		Initialized by a list of the suits and values which the cards may
		hold (suits and values can be represented by chars only). Holds 
		std::vectors containing the suits and values.
	Card class:
		Represents a playing card. Only holds the index to the name of the
		suit/value in the deck array so the deck class must be provided
		if trying to examine a human-readable version of the card. Suits and
		values are guaranteed to be held in the order inserted into the deck
		class so comparisons between playing cards is automatic
	Hand typedef:
		A hand is synonymous with std::vector<Card>
	Auxillary functions:
		deal:
			Takes a card from a hand and returns it. If the card was not in
			the hand, returns an impossible card (which can be checked using
			the is_valid() member function of Card). If no particular card
			is chosen, the last is taken. 
		deal_n: 
			Takes the top n cards from a hand and puts them into the second
			hand. If the first hand contains less than n cards, the function
			returns false
		deal_all:
			Creates a Hand containing all possible cards in a deck
		shuffle:
			Shuffles a Hand in-place
*/

#include <initializer_list>
#include <vector>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "std_exception.h"

namespace playing_cards
{
	DERIVE_FROM_STD_EXCEPTION(invalid_card);

	class Card;
	typedef std::vector<Card> Hand;

	class Deck
	{
	public:
		Deck(const std::initializer_list<char>& suits, const std::initializer_list<char>& values) :
			Deck(suits.begin(), suits.end(), values.begin(), values.end()) {}
		template <class It>
		Deck(It suits_begin, It suits_end, It values_begin, It values_end) :
			suits(suits_begin, suits_end), values(values_begin, values_end) {}
		unsigned int suit_id(char suit) { return std::distance(suits.begin(), std::find(suits.begin(), suits.end(), suit)); }
		unsigned int value_id(char value) { return std::distance(values.begin(), std::find(values.begin(), values.end(), value)); }
		const std::vector<char> suits, values;
	};

	class Card
	{
	public:
		Card() : suit(-1), value(-1) {}
		Card(unsigned int suit_id, unsigned int value_id) : suit(suit_id), value(value_id) {}
		Card(char suit, char value, const Deck& deck) :
			suit(std::distance(deck.suits.begin(), std::find(deck.suits.begin(), deck.suits.end(), suit))),
			value(std::distance(deck.values.begin(), std::find(deck.values.begin(), deck.values.end(), value)))
		{
			if (this->suit >= deck.suits.size() || this->value >= deck.values.size())
				throw invalid_card("Tried to make an invalid card!");
		}
		char get_suit(const Deck& deck) const { return deck.suits[suit]; }
		char get_value(const Deck& deck) const { return deck.values[value]; }
		bool is_valid(const Deck& deck) const { return suit < deck.suits.size() && value < deck.values.size(); }
		bool operator == (const Card& card) const { return suit == card.suit && value == card.value; }
		bool operator < (const Card& card) const { if (suit == card.suit) return value < card.value; else return suit < card.suit; }
		unsigned int suit, value;
	};

	inline Card deal(Hand& hand, Card card)
	{
		auto pos = std::find(hand.begin(), hand.end(), card);
		if (pos == hand.end())
			return Card(-1, -1);
		else {
			hand.erase(pos);
			return card;
		}
	}

	inline Card deal(Hand& hand)
	{
		if (hand.size() == 0)
			return Card(-1, -1);
		else {
			Card card = hand.back();
			hand.pop_back();
			return card;
		}
	}

	inline Card deal_random(Hand& hand)
	{
		if (hand.size() == 0)
			return Card(-1, -1);
		else {
			auto it = hand.begin();
			std::advance(it, rand() % hand.size());
			Card card = *it;
			hand.erase(it);
			return card;
		}

	}

	inline bool deal_n(Hand& from, unsigned int n, Hand& to)
	{
		bool big_enough = from.size() >= n;
		if (!big_enough)
			n = from.size();
		while (n--) {
			Card card = from.back();
			from.pop_back();
			to.push_back(card);
		}
		return big_enough;
	}

	inline Hand deal_n(Hand& from, unsigned int n)
	{
		Hand to;
		deal_n(from, n, to);
		return to;
	}

	inline Hand deal_all(const Deck& deck)
	{
		Hand hand(deck.suits.size() * deck.values.size());
		for (unsigned int i = 0; i < hand.size(); ++i)
			hand[i] = Card(i % deck.suits.size(), i / deck.suits.size());
		return hand;
	}

	inline void shuffle(Hand& hand)
	{
		srand(time(0));
		std::random_shuffle(hand.begin(), hand.end());
	}

	inline void sort_suits(Hand& hand)
	{
		std::sort(hand.begin(), hand.end(), [](const Card& lhs, const Card& rhs)
		{
			if (lhs.suit == rhs.suit)
				return lhs.value < rhs.value;
			else
				return lhs.suit < rhs.suit;
		});
	}

	inline void sort_values(Hand& hand)
	{
		std::sort(hand.begin(), hand.end(), [](const Card& lhs, const Card& rhs)
		{
			if (lhs.value == rhs.value)
				return lhs.suit < rhs.suit;
			else
				return lhs.value < rhs.value;
		});
	}

	inline std::string to_string(const Card& card, const Deck& deck)
	{
		return std::string(1, card.get_suit(deck)) + std::string(1, card.get_value(deck));
	}

	inline std::string to_string(Hand hand, const Deck& deck)
	{
		sort_suits(hand);
		std::string str;
		unsigned int cur_suit = -1;
		for (const Card& card : hand) {
			if (cur_suit != card.suit) {
				str += std::string(" (") + card.get_suit(deck) + ") ";
				cur_suit = card.suit;
			}
			str += card.get_value(deck);
		}
		return str;
	}

	inline Deck standard_52()
	{
		return Deck(
			{'D', 'C', 'H', 'S'},
			{'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'}
		);
	}

}