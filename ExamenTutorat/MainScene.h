#ifndef _MAIN_SCENE_H_
#define	_MAIN_SCENE_H_

#include <Scene.h>
#include "SFML/Graphics.hpp"
#include "Paddle.h"
#include "PongBall.h"
#include "Brick.h"

class MainScene :
	public ggf::Scene
{
public:

	MainScene(ggf::Game& game);
	virtual ~MainScene();

	void initCurrent() override;
	void updateCurrent(const sf::Time& dt) override;
	void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
	void cleanupCurrent() override;

	void onKeyPressed(const ggf::EventData &data);
	void onKeyReleased(const ggf::EventData &data);

private:
	bool CheckCollisions();
	void HandlePongBall();
	void HandleBrickHits();
	void HandleSafeHaven();

	void SetupBricks();

	Paddle::Ptr m_paddle;
	PongBall::Ptr m_pongBall;

	std::vector<std::vector<Brick::Ptr> > bricks;
	sf::Vector2f m_safeHaven;
	int m_safeHavenCount;
};

#endif //_MAIN_SCENE_H_