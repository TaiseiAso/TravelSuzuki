#include <string>
#include "timer.h"
#include "device/fps/fps_controller.h"
#include "device/text/font_manager.h"

namespace game::timer
{
	Timer::Timer(int x, int y, int fontSize)
		: x_(x),
		  y_(y),
		  remainTime_(0.f),
		  isFinished_(false),
		  isStop_(false)
	{
		text::FontManager::instance().createFont("Voyager Grotesque Bold", "timerFont", fontSize, 6, DX_FONTTYPE_ANTIALIASING);
		fontHandle_ = text::FontManager::instance().getFontHandle("timerFont");
	}

	Timer::~Timer()
	{
		text::FontManager::instance().deleteFont("timerFont");
	}

	void Timer::update()
	{
		if (!isFinished_ && !isStop_)
		{
			remainTime_ -= 1.f / fps::FPSController::FPS;
			if (remainTime_ <= 0.f)
			{
				remainTime_ = 0.f;
				isFinished_ = true;
			}
		}
	}

	void Timer::draw() const
	{
		DrawFormatStringToHandle(
			x_, y_, 
			remainTime_ > 20.f ? whiteColor_ : redColor_, 
			fontHandle_, 
			"%06.2f", remainTime_);
	}

	float Timer::getRemainTime() const
	{
		return remainTime_;
	}

	bool Timer::isFinished() const
	{
		return isFinished_;
	}

	bool Timer::isStop() const
	{
		return isStop_;
	}

	void Timer::setRemainTime(float remainTime)
	{
		remainTime_ = remainTime;
		if (remainTime_ > 0.f) isFinished_ = false;
		else
		{
			remainTime_ = 0.f;
			isFinished_ = true;
		}
	}

	void Timer::stop()
	{
		isStop_ = true;
	}

	void Timer::resume()
	{
		isStop_ = false;
	}
}