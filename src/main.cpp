#include "game.h"

int main(int argc, char* argv[])
{
	Piles piles;
	Display display(800, 800);
	Player dealer = South;
	while (!display.is_active()); //Wait for initialization
	while (display.is_active()) {
		Logic eng(display, dealer);
		eng.play_game();
		dealer = static_cast<Player>((dealer + 1) % 4);
	}
	return 0;
}

