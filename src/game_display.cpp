#include "game.h"

using namespace playing_cards;

sf::Color Display::bg_color = sf::Color(50, 100, 0);

Display::Display() :
	Display(sf::VideoMode::getFullscreenModes().front().width,
		sf::VideoMode::getFullscreenModes().front().height) {}


Display::Display(
	unsigned int width, unsigned int height)
	: width(width), height(height), win_thread(&Display::run, this),
	piles_ptr(nullptr), accept_input(false), input(playing_cards::Card()),
	is_paused(false), window_ptr(nullptr)
{
	using namespace playing_cards;

	//Load card textures
	Deck deck = standard_52();
	Hand pile = deal_all(deck);
	for (const Card& card : pile) {
		sf::Texture t;
		t.loadFromFile("../share/card_textures/" + to_string(card, deck) + ".jpg");
		card_textures[card] = t;
	}
	sf::Texture t;
	t.loadFromFile("../share/card_textures/back.jpg");
	card_textures[Card()] = t;

	resize();

	//Begin the engine
	win_thread.detach();
}

void Display::resize()
{
	//Calculate card size and spacing
	card_size.y = height / 8;
	card_size.x = height / 11;
	card_spacing.x = card_size.x / 3;
	card_spacing.y = card_size.y / 2;
}

void Display::set_piles(Piles* piles)
{
	piles_ptr = piles;
}

bool Display::is_active()
{
	return window_ptr != nullptr;
}

playing_cards::Card Display::get_input()
{
	accept_input = true;
	while (is_active()) {
		if (input == Card())
			continue;
		else {
			Card card = input;
			input = Card();
			return card;
		}
	}
}

void Display::pause()
{
	g_mutex.lock();
	is_paused = true;
	g_mutex.unlock();
	bool in_paused;
	while (is_active()) {
		g_mutex.lock();
		in_paused = is_paused;
		g_mutex.unlock();
		if (in_paused == false)
			return;
	}
}

void Display::run()
{
	bool fullscreen = (height == sf::VideoMode::getFullscreenModes().front().height);
	sf::VideoMode video_mode = fullscreen 
		? sf::VideoMode::getFullscreenModes().front()
		: sf::VideoMode(width, height);
	unsigned int style = fullscreen
		? sf::Style::None
		: sf::Style::Default;

	sf::RenderWindow window(
		video_mode,
		"Boxes",
		style);
	sf::Image icon;
	icon.loadFromFile("resources/icon.jpg");
	if (icon.getSize().x != 0)
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window_ptr = &window;
	while (window.isOpen()) {
		//Poll events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Handle close event
			if (event.type == sf::Event::Closed) {
				window_ptr = nullptr;
				window.close();
				return;
			}

			//Mouse button events
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					g_mutex.lock();
					is_paused = false;
					if (accept_input) {
						for (auto it = card_rects.rbegin(); it != card_rects.rend(); ++it) {
							auto elem = *it;
							if (elem.second.contains(
								event.mouseButton.x, event.mouseButton.y)) {
								input = elem.first;
								break;
							}
						}
					}
					g_mutex.unlock();
				}
			}

			//Window resize
			if (event.type == sf::Event::Resized) {
				width = window.getSize().x;
				height = window.getSize().y;
				window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				resize();
			}

		}

		//Draw routine
		window.clear(bg_color);
		card_rects.clear();
		g_mutex.lock();
		if (piles_ptr) {
			draw_players();
			draw_cribs();
			draw_piles();
			draw_tricks();
		}
		g_mutex.unlock();
		window.display();
	}
}

void Display::draw_card(const playing_cards::Card& card, const sf::Vector2f& pos, bool rotate_90)
{
	const sf::Texture& texture = card_textures.at(card);
	sf::Vector2f scale(card_size.x / texture.getSize().x, card_size.y / texture.getSize().y);
	sf::Sprite sprite(texture);
	if (rotate_90)
		sprite.setRotation(-90);
	sprite.setPosition(pos);
	sprite.setScale(scale);
	window_ptr->draw(sprite);
}

void Display::draw_players()
{
	playing_cards::Card card_back;
	sf::Vector2f pos;
	unsigned int n;
	
	//South player - center-bottom face up
	n = piles_ptr->players[South].size();
	pos.x = (width - (n - 1) * card_spacing.x - card_size.x) / 2;
	pos.y = height - card_size.y;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(piles_ptr->players[South][i], pos);
		card_rects.push_back(std::make_pair(
			piles_ptr->players[South][i], sf::FloatRect(pos, card_size)));
		pos += sf::Vector2f(card_spacing.x, 0);
	}

	//North player - center-top face down
	n = piles_ptr->players[North].size();
	pos.x = (width - (n - 1) * card_spacing.x - card_size.x) / 2;
	pos.y = 0;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(card_back, pos);
		pos += sf::Vector2f(card_spacing.x, 0);
	}

	//West player - left-middle face down
	n = piles_ptr->players[West].size();
	pos.x = 0;
	pos.y = (2 * height - (n - 1) * card_spacing.x - card_size.x) / 4;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(card_back, pos, true);
		pos += sf::Vector2f(0, card_spacing.x);
	}

	//East player - right-middle face down
	n = piles_ptr->players[East].size();
	pos.x = width - card_size.y;
	pos.y = (2 * height - (n - 1) * card_spacing.x - card_size.x) / 4;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(card_back, pos, true);
		pos += sf::Vector2f(0, card_spacing.x);
	}
}

void Display::draw_cribs()
{
	sf::Vector2f pos;
	unsigned int n;

	//South crib
	n = piles_ptr->cribs[South].size();
	pos.x = (width - card_size.x * n) / 2;
	pos.y = height - 2 * card_size.y - card_spacing.y;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(piles_ptr->cribs[South][i], pos);
		card_rects.push_back(std::make_pair(
			piles_ptr->cribs[South][i], sf::FloatRect(pos, card_size)));
		pos += sf::Vector2f(card_size.x, 0);
	}

	//North crib
	n = piles_ptr->cribs[North].size();
	pos.x = (width - card_size.x * n) / 2;
	pos.y = card_size.y + card_spacing.y;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(piles_ptr->cribs[North][i], pos);
		pos += sf::Vector2f(card_size.x, 0);
	}

	//West crib
	n = piles_ptr->cribs[West].size();
	pos.y = (height - card_size.x * n) / 2 + card_size.x;
	pos.x = width / 2 - 3 * card_size.x / 2 - card_spacing.x - card_size.y;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(piles_ptr->cribs[West][i], pos, true);
		pos += sf::Vector2f(0, card_size.x);
	}

	//East crib
	n = piles_ptr->cribs[East].size();
	pos.y = (height - card_size.x * n) / 2 + card_size.x;
	pos.x = width / 2 + 3 * card_size.x / 2 + card_spacing.x;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(piles_ptr->cribs[East][i], pos, true);
		pos += sf::Vector2f(0, card_size.x);
	}
}

void Display::draw_piles()
{
	Card card_back;
	sf::Vector2f pos;
	unsigned int n;

	//NS Pile
	n = piles_ptr->ns_pile.size();
	pos.x = 0;
	pos.y = height - card_size.y;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(piles_ptr->show_piles ? piles_ptr->ns_pile[i] : card_back, pos);
		pos.x += card_spacing.x / 2;
	}

	//EW Pile
	n = piles_ptr->ew_pile.size();
	pos.x = width - card_size.x;
	pos.y = height - card_size.y;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(piles_ptr->show_piles ? piles_ptr->ew_pile[i] : card_back, pos);
		pos.x -= card_spacing.x / 2;
	}

	//Discards
	n = piles_ptr->discard_pile.size();
	pos.x = width - card_size.x;
	pos.y = 0;
	for (unsigned int i = 0; i < n; ++i) {
		draw_card(piles_ptr->show_piles ? piles_ptr->discard_pile[i] : card_back, pos);
		pos.x -= card_spacing.x / 2;
	}

}

void Display::draw_tricks()
{
	sf::Vector2f pos;
	unsigned int n;

	//Prev pile
	n = piles_ptr->prev_trick.size();
	pos.x = card_size.x / 2;
	pos.y = card_size.y / 4;
	for (unsigned int i = 0; i < n; ++i) {
		switch ((piles_ptr->prev_lead + i) % 4) {
		case South:
			draw_card(piles_ptr->prev_trick[i], pos + sf::Vector2f(0, card_size.y / 4));
			break;
		case West:
			draw_card(piles_ptr->prev_trick[i], pos - sf::Vector2f(card_size.x / 2, 0));
			break;
		case North:
			draw_card(piles_ptr->prev_trick[i], pos - sf::Vector2f(0, card_size.y / 4));
			break;
		case East:
			draw_card(piles_ptr->prev_trick[i], pos + sf::Vector2f(card_size.x / 2, 0));
			break;
		}
	}

	//Cur pile
	n = piles_ptr->cur_trick.size();
	pos.x = width / 2 - card_size.x / 2;
	pos.y = height / 2 - card_size.y / 2;
	for (unsigned int i = 0; i < n; ++i) {
		switch ((piles_ptr->cur_lead + i) % 4) {
		case South:
			draw_card(piles_ptr->cur_trick[i], pos + sf::Vector2f(0, card_size.y / 4));
			break;
		case West:
			draw_card(piles_ptr->cur_trick[i], pos - sf::Vector2f(card_size.x / 2, 0));
			break;
		case North:
			draw_card(piles_ptr->cur_trick[i], pos - sf::Vector2f(0, card_size.y / 4));
			break;
		case East:
			draw_card(piles_ptr->cur_trick[i], pos + sf::Vector2f(card_size.x / 2, 0));
			break;
		}
	}
}