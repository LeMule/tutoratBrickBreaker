#ifndef __BRICK_H__
#define __BRICK_H__

#include "Entity.h"

class Brick :
	public ggf::Entity
{
public:
	enum BrickState
	{
		FULL_HEALTH,
		MID_HEALTH,
		LOW_HEALTH,
		DEAD
	};
	typedef std::shared_ptr<Brick> Ptr;

	Brick(ggf::Scene &aScene);
	~Brick();

	virtual void initCurrent();
	virtual void updateCurrent(const sf::Time& dt);
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void cleanupCurrent();

	sf::FloatRect getGlobalBoundsJF();
	sf::Vector2f getPosition();
	BrickState getState();
	void setState(BrickState state);

	void handleHit();
	
private:
	int generateRandomRGB();

	sf::RectangleShape m_brick;
	BrickState m_state;
	std::vector<sf::Color> m_stateColors;

	
};

#endif // __BRICK_H__

