#include "Paddle.h"

Paddle::Paddle(ggf::Scene &aScene)
	: ggf::Entity(aScene)
	, paddle()
{
	paddle = sf::RectangleShape(sf::Vector2f(100, 25));
	paddle.setFillColor(sf::Color::Cyan);
	paddle.setPosition(sf::Vector2f(350.0, 500.0));
}

Paddle::~Paddle()
{
}

void Paddle::initCurrent() 
{}

void Paddle::updateCurrent(const sf::Time& dt) 
{
	paddle.move(getVelocity());
}

void Paddle::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const 
{
	target.draw(paddle, states);
}

void Paddle::cleanupCurrent() {}

sf::FloatRect Paddle::getGlobalBoundsJF()
{
	return getTransform().transformRect(paddle.getGlobalBounds());
}

sf::Vector2f Paddle::getPosition()
{
	return paddle.getPosition();
}

