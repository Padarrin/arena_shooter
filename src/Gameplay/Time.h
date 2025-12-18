#pragma once

class Time
{
protected:
	float mTime;
	float mCurrenteTime;
	int mPhaseFinish;
public:
	Time() { SetTime(0.f); }
	Time(float time) { SetTime(time); }

	void Update(float deltatime) 
	{ 
		mCurrenteTime -= deltatime;
		if (mCurrenteTime > 0.f)
		{
			mPhaseFinish = 0;
		}
		else
		{
			if (mPhaseFinish == 0)
			{
				mPhaseFinish = 1;
			}
			else
			{
				mPhaseFinish = 2;
			}
		}
	}

	void Reset() { mCurrenteTime = mTime; }

	void SetTime(float time) { mTime = time; mCurrenteTime = time; }
	float GetTime() { return mTime; }

	int GetCurrenteTime() { return mCurrenteTime; }

	bool IsFinish() { return mCurrenteTime < 0.f; }
	bool GetIsNotFinish() { return mPhaseFinish == 0; }
	bool GetIsFinishNow() { return mPhaseFinish == 1; }
	bool GetIsFinishSinceLong() { return mPhaseFinish == 2; }
};

