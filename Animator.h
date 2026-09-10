#pragma once

class Animator
{
public:

	Animator() = default;
	int GetFrame(Sprite* sprite, float FPS, float deltatime,bool, int animationId = -1);
	void Reset() { _animationTimer = 0; _finished = false; }
	bool Finished() { return _finished; }
private:

	float GetAnimationTime(int frameCount, int fps);
	float _animationTimer = 0;
	Sprite* _lastSprite = nullptr;
	int _lastAnimationId = -1;
	bool _finished = false;
};

