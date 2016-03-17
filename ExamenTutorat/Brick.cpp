#include "Brick.h"

Brick::Brick(ggf::Scene &aScene)
	:ggf::Entity(aScene)
	, m_brick()
	, m_state(BrickState::FULL_HEALTH)
{
	m_stateColors.resize(4, sf::Color());
	m_stateColors.at(0) = sf::Color(generateRandomRGB(), 0, 0, 255);
	m_stateColors.at(1) = sf::Color(0, generateRandomRGB(), 0, 255);
	m_stateColors.at(2) = sf::Color(0, 0, generateRandomRGB(), 255);
	m_stateColors.at(3) = sf::Color(0, 0, 0, 0);
}

Brick::~Brick()
{

}

void Brick::initCurrent() 
{
	m_brick = sf::RectangleShape(sf::Vector2f(100, 25));
	m_brick.setFillColor(m_stateColors.at(0));
}

void Brick::updateCurrent(const sf::Time& dt)
{
	switch (m_state)
	{
	default:
	case BrickState::FULL_HEALTH:
		m_brick.setFillColor(m_stateColors.at(0));
		break;
	case BrickState::MID_HEALTH:
		m_brick.setFillColor(m_stateColors.at(1));
		break;
	case BrickState::LOW_HEALTH:
		m_brick.setFillColor(m_stateColors.at(2));
		break;
	case BrickState::DEAD:
		m_brick.setFillColor(m_stateColors.at(3));
		break;
	}
}

void Brick::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	if(m_state != BrickState::DEAD)
		target.draw(m_brick, states);
}

void Brick::cleanupCurrent() {}

sf::FloatRect Brick::getGlobalBoundsJF()
{
	return getTransform().transformRect(m_brick.getGlobalBounds());
}

sf::Vector2f Brick::getPosition()
{
	return m_brick.getPosition();
}

void Brick::handleHit()
{
	switch (m_state)
	{
	default:
	case BrickState::FULL_HEALTH:
		m_state = BrickState::MID_HEALTH;
		break;
	case BrickState::MID_HEALTH:
		m_state = BrickState::LOW_HEALTH;
		break;
	case BrickState::LOW_HEALTH:
		m_state = BrickState::DEAD;
		break;
	}
}

Brick::BrickState Brick::getState()
{
	return m_state;
}

void Brick::setState(Brick::BrickState state)
{
	m_state = state;
}

int Brick::generateRandomRGB()
{
	int randomRGB = 0;
	randomRGB = rand() % 255 + 1;
	if (randomRGB < 100)
		randomRGB += 100;
	return randomRGB;
}