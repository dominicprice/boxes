//#include "game.h"
//
//int main(int argc, char* argv[])
//{
//	Piles piles;
//	Display display(800, 800);
//	Player dealer = South;
//	while (!display.is_active()); //Wait for initialization
//	while (display.is_active()) {
//		Logic eng(display, dealer);
//		eng.play_game();
//		dealer = static_cast<Player>((dealer + 1) % 4);
//	}
//	return 0;
//}

#include <SFML/Graphics.hpp>
#include "cards.hpp"

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("cute_image.jpg"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		return EXIT_FAILURE;
	sf::Text text("Hello SFML", font, 50);
	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Clear screen
		window.clear();
		// Draw the sprite
		window.draw(sprite);
		// Draw the string
		window.draw(text);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}
