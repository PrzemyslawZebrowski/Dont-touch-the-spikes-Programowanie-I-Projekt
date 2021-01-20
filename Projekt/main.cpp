#include <SFML/Graphics.hpp>
#include "definicje.h"
#include "Game.h"
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    Game game(SZERKOKOSC_OKNA, WYSKOKOSC_OKNA, string("Don't touch the spikes 2.0"));
}
