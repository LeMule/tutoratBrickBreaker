#include "MainScene.h"
#include "Paddle.h"
#include "PongBall.h"
#include <Game.h>

MainScene::MainScene(ggf::Game& game)
	:Scene(game)
	, m_paddle(new Paddle(*this))
	, m_pongBall(new PongBall(*this))
	, m_safeHavenCount(0)
{
	m_safeHaven.x = -300;
	m_safeHaven.y = -200;

	bricks.resize(4);
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks.at(i).resize(8);
		for (int j = 0; j < bricks.at(i).size(); j++)
		{
			bricks.at(i).at(j) = std::shared_ptr<Brick>(new Brick(*this));
			attachChild(bricks.at(i).at(j));
		}
	}

	attachChild(m_paddle);
	attachChild(m_pongBall);

	getGame().getEventManager().subscribe(sf::Event::KeyPressed, &MainScene::onKeyPressed, this);
	getGame().getEventManager().subscribe(sf::Event::KeyReleased, &MainScene::onKeyReleased, this);
}

MainScene::~MainScene()
{

}

void MainScene::initCurrent()
{
	SetupBricks();
	m_pongBall->setVelocity(5, 5);
}

void MainScene::updateCurrent(const sf::Time& dt)
{
	HandlePongBall();
	HandleBrickHits();
	HandleSafeHaven();
}

void MainScene::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.clear();
}

void MainScene::cleanupCurrent()
{
	
}

void MainScene::onKeyPressed(const ggf::EventData & data)
{
	auto keyEvent = data.getDataAs<sf::Event::KeyEvent>();
	sf::Vector2f newVelocity = m_paddle->getVelocity();
	switch (keyEvent.code)
	{
	case sf::Keyboard::Left:
		newVelocity.x = m_paddle->getVelocity().x - 10;
		break;
	case sf::Keyboard::Right:
		newVelocity.x = m_paddle->getVelocity().x + 10;
		break;
	default:
		break;
	}
	m_paddle->setVelocity(newVelocity);
}

void MainScene::onKeyReleased(const ggf::EventData & data)
{
	auto keyEvent = data.getDataAs<sf::Event::KeyEvent>();

	switch (keyEvent.code)
	{
	case sf::Keyboard::Left:
	case sf::Keyboard::Right:
		m_paddle->setVelocity(0, m_paddle->getVelocity().y);
		break;
	default:
		break;
	}
}

bool MainScene::CheckCollisions()
{
	if (m_paddle->getGlobalBoundsJF().intersects(m_pongBall->getGlobalBoundsJF()))
	{
		return true;
	}
	return false;
}

void MainScene::HandlePongBall()
{
	if (CheckCollisions())
	{
		m_pongBall->setVelocity(m_pongBall->getVelocity().x, -m_pongBall->getVelocity().y);
	}
	float tempX = m_pongBall->getPosition().x;
	float tempY = m_pongBall->getPosition().y;
	if (tempX >= 790.0 || tempX <= 0.0)
	{
		m_pongBall->setVelocity(-m_pongBall->getVelocity().x, m_pongBall->getVelocity().y);
	}
	if (tempY >= 590.0 || tempY <= 0.0)
	{
		m_pongBall->setVelocity(m_pongBall->getVelocity().x, -m_pongBall->getVelocity().y);
	}
}

void MainScene::HandleBrickHits()
{
	for (int i = 0; i < bricks.size(); i++)
	{
		for (int j = 0; j < bricks.at(i).size(); j++)
		{
			if (bricks.at(i).at(j)->getGlobalBoundsJF().intersects(m_pongBall->getGlobalBoundsJF()))
			{
				if (bricks.at(i).at(j)->getState() == Brick::BrickState::DEAD)
				{
					bricks.at(i).at(j)->setPosition(m_safeHaven);
					m_safeHavenCount++;
				}
				bricks.at(i).at(j)->handleHit();
				m_pongBall->setVelocity(m_pongBall->getVelocity().x, -m_pongBall->getVelocity().y);
			}
		}
	}
}

void MainScene::HandleSafeHaven()
{
	if (m_safeHavenCount == 32)
	{
		SetupBricks();
	}
}

void MainScene::SetupBricks()
{
	float xPos = 100.0;
	float yPos = 25.0;

	for (int i = 0; i < bricks.size(); i++)
	{
		for (int j = 0; j < bricks.at(i).size(); j++)
		{
			bricks.at(i).at(j)->setPosition(sf::Vector2f(xPos*j, yPos*i));
		}
	}
}