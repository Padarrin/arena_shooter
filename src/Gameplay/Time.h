#pragma once

class Time
{
protected:
	float mTime;
	float mCurrenteTime;
public:
	Time() { SetTime(0.f); }
	Time(float time) { SetTime(time); }

	void Update(float timeElapsed) { mCurrenteTime -= timeElapsed; }

	void Reset() { mCurrenteTime = mTime; }

	void SetTime(float time) { mTime = time; mCurrenteTime = time; }
	float GetTime() { return mTime; }

	bool IsFinish() { return mCurrenteTime < 0.f; }
	int GetCurrenteTime() { return mCurrenteTime; }
};

