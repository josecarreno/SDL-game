#include <SDL.h>

void init() {}
void render() {}
void update() {}
void handleEvents() {}
void clean() {}

bool g_bRunning = true;

int main()
{
	init();
	while (g_bRunning)
	{
		handleEvents();
		update();
		render();
	}
	clean();
}