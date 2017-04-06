#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "playing_cards.h"

enum Player : unsigned int
{
	South	= 0,
	West	= 1,
	North	= 2,
	East	= 3,
	Anon	= 4
};

struct Piles
{
	Piles() :
		players(4), cribs(4), show_piles(false) {}
	std::vector<playing_cards::Hand> players, cribs;
	playing_cards::Hand ns_pile, ew_pile, discard_pile, cur_trick, prev_trick;
	Player prev_lead, cur_lead;
	bool show_piles;
};

extern std::mutex g_mutex;

class Display
{
public:
	Display();
	Display(unsigned int width, unsigned int height);

	bool is_active();
	playing_cards::Card get_input();
	void set_piles(Piles* piles);
	void pause();

	unsigned int height, width;
private:
	void run();

	//Drawing function
	void draw_players();
	void draw_cribs();
	void draw_piles();
	void draw_tricks();
	void draw_card(const playing_cards::Card& card, const sf::Vector2f& pos, 
		bool rotate_90 = false);
	void resize();
	static sf::Color bg_color;
	std::mutex m_lock;
	bool accept_input;
	bool is_paused;
	playing_cards::Card input;
	std::thread win_thread;
	sf::RenderWindow* window_ptr;
	Piles* piles_ptr;

	std::vector<std::pair<playing_cards::Card, sf::FloatRect>> card_rects;
	std::map<playing_cards::Card, sf::Texture> card_textures;
	sf::Vector2f card_size, card_spacing;
};

class Logic
{
public:
	Logic(Display& display, Player dealer);
	~Logic();
	void play_game();
private:
	bool stage_discard();
	bool stage_tricks();
	bool stage_cribs();
	std::vector<Player> play_order(Player lead);
	void play_discard(Player pos);
	void play_trick(Player pos, playing_cards::Hand& hand);
	Player calculate_winner();
	bool contains_jack(playing_cards::Hand& hand);
	Display& display;
	Piles piles;
	playing_cards::Deck deck;
	Player dealer;
};