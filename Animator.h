#pragma once

class Animator
{
public:

	Animator() = default;
	int GetFramesLoop(Sprite* sprite, float FPS, float deltatime);

	int GetFramesOneShot(Sprite* sprite, float FPS, float deltatime);
	bool IsOneShotFinished() const { return _oneShotFinished; }
	void ResetOneShotTimer() { _oneShotTimer = 0; _oneShotFinished = false; }

private:

	float GetAnimationTime(int frameCount, int fps);

	Sprite* _lastLoopingSprite = nullptr;
	float _loopingTimer = 0;

	float _oneShotTimer = 0;
	bool _oneShotFinished = false;
};

