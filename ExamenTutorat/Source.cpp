#include "Game.h"
#include "MainScene.h"


int main()
{
	ggf::Game game(sf::VideoMode(800, 600), "Brick Breaker");
	game.pushScene(ggf::Scene::Ptr(new MainScene(game)));
	game.start();
}