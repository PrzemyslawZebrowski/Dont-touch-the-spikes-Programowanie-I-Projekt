#include <SFML/Graphics.hpp>
#include "definitions.h"
#include "Game.h"
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    Game game(WINDOW_WIDTH, WINDOW_HEIGHT, string("Don't touch the spikes 2.0"));
}
