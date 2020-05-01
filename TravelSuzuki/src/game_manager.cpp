#include "game_manager.h"

namespace game
{
	GameManager::GameManager()
		: timer_(std::make_unique<timer::Timer>(5, 5, 50))
	{
		timer_->setRemainTime(30.f);
	}

	GameManager::~GameManager()
	{

	}
	
	void GameManager::action()
	{

	}
	
	void GameManager::update()
	{
		timer_->update();
	}
	
	void GameManager::draw() const
	{
		DrawBox(0, 0, 800, 60, blackColor_, TRUE);
		DrawBox(0, 580, 800, 640, blackColor_, TRUE);
		timer_->draw();
	}

	timer::Timer& GameManager::getTimerRef()
	{
		return *timer_;
	}
}