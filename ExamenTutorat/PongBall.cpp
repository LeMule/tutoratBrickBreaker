#include "PongBall.h"

PongBall::PongBall(ggf::Scene &aScene)
	: ggf::Entity(aScene)
{
	pongball = sf::CircleShape(5.0);
	pongball.setFillColor(sf::Color::Magenta);
	pongball.setPosition(sf::Vector2f(350.0, 400.0));
}

PongBall::~PongBall()
{
}

void PongBall::initCurrent() {}
void PongBall::updateCurrent(const sf::Time& dt) 
{
	pongball.move(getVelocity());
}

void PongBall::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const 
{
	target.draw(pongball, states);
}

void PongBall::cleanupCurrent() {}

sf::FloatRect PongBall::getGlobalBoundsJF()
{
	return getTransform().transformRect(pongball.getGlobalBounds());
}

sf::Vector2f PongBall::getPosition()
{
	return pongball.getPosition();
}
