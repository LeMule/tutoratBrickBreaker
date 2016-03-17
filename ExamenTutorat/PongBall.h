#ifndef __PONGBALL_H__
#define __PONGBALL_H__

#include "Scene.h"
#include "Entity.h"

class PongBall :
	public ggf::Entity
{
public:
	typedef std::shared_ptr<PongBall> Ptr;

	PongBall(ggf::Scene &aScene);
	~PongBall();

	virtual void initCurrent();
	virtual void updateCurrent(const sf::Time& dt);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void cleanupCurrent();

	sf::FloatRect getGlobalBoundsJF();
	sf::Vector2f getPosition();

private:
	sf::CircleShape pongball;
};

#endif //__PONGBALL_H__

