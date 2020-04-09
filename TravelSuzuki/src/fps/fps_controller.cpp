#include "fps_controller.h"
#include "Dxlib.h"

namespace game::fps
{
	FPSController::FPSController()
	{
		startTime_ = 0;
		count_ = 0;
		fps_ = 0;
	}

	FPSController::~FPSController() {}

	void FPSController::update()
	{
		if (count_ == 0) startTime_ = GetNowCount();
		else if (count_ == N)
		{
			int t = GetNowCount();
			fps_ = 1000.f / ((t - startTime_) / (float)N);
			count_ = 0;
			startTime_ = t;
		}
		count_++;
	}

	void FPSController::draw() const
	{
		DrawFormatString(760, 620, GetColor(255, 255, 255), "%.1f", fps_);
	}

	void FPSController::wait() const
	{
		int tookTime = GetNowCount() - startTime_;
		int waitTime = count_ * 1000 / FPS - tookTime;
		if (waitTime > 0) Sleep(waitTime);
	}
}