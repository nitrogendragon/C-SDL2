#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();

	game->init("DuncanCorpEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 820, false);
	while (game->running()) 
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
	
}
