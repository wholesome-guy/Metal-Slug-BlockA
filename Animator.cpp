#include "precomp.h"
#include "Animator.h"

int Animator::GetFrame(Sprite* sprite, float FPS, float deltatime, bool loop, int animationId)
{
	bool isSameAnimation;

	if (animationId != -1)
	{
		isSameAnimation = (animationId == _lastAnimationId);
		_lastAnimationId = animationId;
	}
	else
	{
		isSameAnimation = (sprite == _lastSprite);
		_lastSprite = sprite;
	}

	if (!isSameAnimation)
	{
		_animationTimer = 0;
		_finished = false;
	}

	int frameCount = sprite->Frames();
	float animationTime = GetAnimationTime(frameCount, FPS);

	if (animationTime <= 0 || frameCount <= 0) return 0;

	if (!_finished)
	{
		_animationTimer += deltatime;
	}

	if (_animationTimer >= animationTime)
	{
		if (loop)
		{
			_animationTimer = 0;
		}
		else
		{
			_animationTimer = animationTime;
			_finished = true;
		}
	}

	int n = static_cast<int>((_animationTimer / animationTime) * frameCount);

	if (n >= frameCount) n = frameCount - 1;
	return n;
}

float Animator::GetAnimationTime(int frameCount, int FPS)
{
	if (FPS <= 0) return 0;

	return (1000.0f / (float)FPS) * frameCount;
}


