#include "game.h"

using namespace playing_cards;

std::mutex g_mutex;

Logic::Logic(Display& display, Player dealer)
	: display(display), deck(standard_52()), dealer(dealer)
{
	g_mutex.lock();
	piles.discard_pile = deal_all(deck);
	shuffle(piles.discard_pile);
	piles.players = { deal_n(piles.discard_pile, 13), deal_n(piles.discard_pile, 13), deal_n(piles.discard_pile, 13), deal_n(piles.discard_pile, 13) };
	for (Hand& hand : piles.players)
		sort_suits(hand);
	display.set_piles(&piles);
	g_mutex.unlock();
}

Logic::~Logic()
{
	display.set_piles(nullptr);
}

void Logic::play_game()
{
	if (!stage_discard()) return;
	if (!stage_tricks()) return;
	if (!stage_cribs()) return;
	display.pause();
}

bool Logic::stage_discard()
{
	for (unsigned int i = 0; i < 3; ++i) {
		for (Player player : play_order(dealer)) {
			if (!display.is_active()) return false;
			play_discard(player);
		}
	}
	return true;
}

bool Logic::stage_tricks()
{
	g_mutex.lock();
	piles.cur_lead = dealer;
	g_mutex.unlock();
	for (unsigned int i = 0; i < 10; ++i) {
		for (Player player : play_order(piles.cur_lead)) {
			if (!display.is_active()) return false;
			play_trick(player, piles.players[player]);
		}
		display.pause();
		g_mutex.lock();
		piles.prev_lead = piles.cur_lead;
		g_mutex.unlock();
		Player winner = calculate_winner();
		g_mutex.lock();
		piles.cur_lead = winner;
		piles.prev_trick = piles.cur_trick;
		if (contains_jack(piles.prev_trick)) 
			deal_n(piles.cur_trick, 4, piles.discard_pile);
		else {
			if (winner == North || winner == South)
				deal_n(piles.cur_trick, 4, piles.ns_pile);
			else
				deal_n(piles.cur_trick, 4, piles.ew_pile);
		}
		g_mutex.unlock();
	}
	return true;
}

bool Logic::stage_cribs()
{
	g_mutex.lock();
	//Decide who is on lead
	std::vector<unsigned int> lengths(4, 0);
	for (const Card& card : piles.ns_pile)
		++lengths[card.suit];
	unsigned int ns_longest = *std::max_element(lengths.begin(), lengths.end());
	lengths.assign(4, 0);
	for (const Card& card : piles.ew_pile)
		++lengths[card.suit];
	unsigned int ew_longest = *std::max_element(lengths.begin(), lengths.end());
	//Change dealer if one side is losing
	if (ns_longest < ew_longest) {
		if (piles.cur_lead == East || piles.cur_lead == West)
			piles.cur_lead = static_cast<Player>((piles.cur_lead + 1) % 4);
	}
	else if (ns_longest > ew_longest) {
		if (piles.cur_lead == North || piles.cur_lead == South)
			piles.cur_lead = static_cast<Player>((piles.cur_lead + 1) % 4);
	}
	sort_suits(piles.ns_pile);
	sort_suits(piles.ew_pile);
	sort_suits(piles.discard_pile);
	piles.show_piles = true;
	g_mutex.unlock();
	for (unsigned int i = 0; i < 3; ++i) {
		for (Player player : play_order(piles.cur_lead)) {
			if (!display.is_active()) return false;
			play_trick(player, piles.cribs[player]);
		}
		display.pause();
		g_mutex.lock();
		piles.prev_lead = piles.cur_lead;
		g_mutex.unlock();
		Player winner = calculate_winner();
		g_mutex.lock();
		piles.cur_lead = winner;
		piles.prev_trick = piles.cur_trick;
		if (contains_jack(piles.prev_trick))
			deal_n(piles.cur_trick, 4, piles.discard_pile);
		else {
			if (winner == North || winner == South)
				deal_n(piles.cur_trick, 4, piles.ns_pile);
			else
				deal_n(piles.cur_trick, 4, piles.ew_pile);
		}
		sort_suits(piles.ns_pile);
		sort_suits(piles.ew_pile);
		sort_suits(piles.discard_pile);
		g_mutex.unlock();
	}
	return true;
}

bool Logic::contains_jack(Hand& hand)
{
	for (Card& card : hand) {
		if (card.value == deck.value_id('J'))
			return true;
	}
	return false;
}

Player Logic::calculate_winner()
{
	g_mutex.lock();
	Hand trick = piles.cur_trick;
	Player lead = piles.cur_lead;
	g_mutex.unlock();
	unsigned int jack = deck.value_id('J');
	unsigned int queen = deck.value_id('Q');
	unsigned int king = deck.value_id('K');

	Player winner = Anon;
	for (int j = trick.size() - 1; j >= 0; --j) {
		if (trick[j].value == king) {
			winner = static_cast<Player>((lead + j) % 4);
			break;
		}
	}
	if (winner == Anon) {
		bool is_queen = false;
		for (unsigned int j = 0; j < trick.size(); ++j) {
			if (trick[j].value == queen) {
				is_queen = true;
				break;
			}
		}
winner = lead;
unsigned int lead_suit = trick[0].suit;
unsigned int lead_value = trick[0].value;
if (is_queen) {
	for (unsigned int j = 1; j < trick.size(); ++j) {
		if (trick[j].suit == lead_suit && trick[j].value < lead_value) {
			winner = static_cast<Player>((lead + j) % 4);
			lead_value = trick[j].value;
		}
	}
}
else {
	if (lead_value == jack)
		lead_value = 0;
	for (unsigned int j = 1; j < trick.size(); ++j) {
		if (trick[j].suit == lead_suit && trick[j].value >= lead_value && trick[j].value < jack) {
			winner = static_cast<Player>((lead + j) % 4);
			lead_value = trick[j].value;
		}
	}
}
	}
	return winner;
}


void Logic::play_discard(Player pos)
{
	unsigned int ten = deck.value_id('T');
	if (pos == South) {
		if (!display.is_active()) return;
		Card card = display.get_input();
		g_mutex.lock();
		while (std::find(piles.players[South].begin(), piles.players[South].end(), card) == piles.players[South].end() ||
			card.value > ten) {
			g_mutex.unlock();
			if (!display.is_active()) return;
			card = display.get_input();
			g_mutex.lock();
		}
		piles.cribs[South].push_back(deal(piles.players[South], card));
	}
	else {
		//Robot thinking time
		sf::sleep(sf::milliseconds(350));
		g_mutex.lock();
		//Always discard highest from shortest suit
		std::vector<unsigned int> lengths(4, 0);
		for (const Card& card : piles.players[pos])
			if (card.value <= ten)
				++lengths[card.suit];
		unsigned int min_length = 14;
		unsigned int suit = 0;
		for (unsigned int i = 0; i < lengths.size(); ++i) {
			if (lengths[i] < min_length && lengths[i] != 0) {
				min_length = lengths[i];
				suit = i;
			}
		}
		Hand possible_plays;
		std::copy_if(piles.players[pos].begin(), piles.players[pos].end(), std::back_inserter(possible_plays),
			[&](const Card& card) {return card.suit == suit && card.value <= ten;});
		sort_values(possible_plays);
		if (possible_plays.size() == 0)
			piles.cribs[pos].push_back(deal_random(piles.players[pos]));
		else
			piles.cribs[pos].push_back(deal(piles.players[pos], possible_plays.back()));
	}
	g_mutex.unlock();
}

void Logic::play_trick(Player pos, Hand& hand)
{
	if (pos == South) {
		Card card = display.get_input();
		g_mutex.lock();
		while (std::find(hand.begin(), hand.end(), card) == hand.end() || ((piles.cur_trick.size() != 0) &&
			(std::count_if(hand.begin(), hand.end(), [&](Card c) {return c.suit == piles.cur_trick[0].suit;}) > 0) && card.suit != piles.cur_trick[0].suit)) {
			g_mutex.unlock();
			if (!display.is_active()) return;
			card = display.get_input();
			g_mutex.lock();
		}
		piles.cur_trick.push_back(deal(hand, card));
	}
	else {
		//Robot thinking time
		sf::sleep(sf::milliseconds(350));
		g_mutex.lock();
		if (piles.cur_trick.empty())
			piles.cur_trick.push_back(deal_random(hand));
		else {
			Hand possible_cards;
			for (unsigned int i = 0; i < hand.size(); ++i) {
				if (hand[i].suit == piles.cur_trick[0].suit)
					possible_cards.push_back(hand[i]);
			}
			Card play;
			if (possible_cards.empty()) {
				possible_cards.assign(hand.begin(), hand.end());
				sort_values(possible_cards);
				play = possible_cards.front();
			}
			else if (piles.cur_trick.size() == 1) {
				if (piles.cur_trick[0].value > deck.value_id('9'))
					play = possible_cards.front();
				else
					play = possible_cards.back();
			}
			else {
				sort_values(possible_cards);
				if (piles.cur_trick.size() > 1) {
					//Partner has played a trick
					Card p_play = piles.cur_trick[piles.cur_trick.size() - 2];
					g_mutex.unlock();
					if (calculate_winner() == (pos + 2) % 4)
						play = possible_cards.front();
					else {
						bool has_honour = false;
						unsigned int ten = deck.value_id('T');
						for (const Card& card : piles.cur_trick) {
							if (card.value > ten) {
								has_honour = true;
								break;
							}
						}
						if (has_honour) {
							play = possible_cards.front();
						}
						else
							play = possible_cards.back();
					}
					g_mutex.lock();
				}
			}
			piles.cur_trick.push_back(deal(hand, play));
		}
	}
	g_mutex.unlock();
}

std::vector<Player> Logic::play_order(Player lead)
{
	std::vector<Player> v(4);
	for (unsigned int i = 0; i < 4; ++i) {
		v[i] = static_cast<Player>((i + lead) % 4);
	}
	return v;
}