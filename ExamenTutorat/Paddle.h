#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "Scene.h"
#include "Entity.h"

class Paddle :
	public ggf::Entity
{
public:
	typedef std::shared_ptr<Paddle> Ptr;

	Paddle(ggf::Scene &aScene);
	~Paddle();

	virtual void initCurrent();
	virtual void updateCurrent(const sf::Time& dt);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void cleanupCurrent();

	sf::FloatRect getGlobalBoundsJF();
	sf::Vector2f getPosition();

private:
	sf::RectangleShape paddle;
};

#endif //__PADDLE_H__

