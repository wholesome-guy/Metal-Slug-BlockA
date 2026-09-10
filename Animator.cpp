#include "precomp.h"
#include "Animator.h"

int Animator::GetFramesLoop(Sprite* sprite, float FPS, float deltatime)
{
	if (sprite != _lastLoopingSprite)
	{
		_lastLoopingSprite = sprite;
		_loopingTimer = 0;
	}

	int frameCount = sprite->Frames();
	float animationTime = GetAnimationTime(frameCount, FPS);

	if (animationTime <= 0 || frameCount <= 0) return 0;


	if (_loopingTimer >= animationTime)
	{
		_loopingTimer = 0;
	}
	else
	{
		_loopingTimer += deltatime;
	}

	int n = static_cast<int>((_loopingTimer / animationTime) * frameCount);

	if (n >= frameCount) n = frameCount - 1;
	return n;
}

int Animator::GetFramesOneShot(Sprite* sprite, float FPS, float deltatime)
{
	int frameCount = sprite->Frames();
	float animationTime = GetAnimationTime(frameCount, FPS);

	if(animationTime <= 0 || frameCount <= 0)
	{
		return 0;
	}

	
		if (_oneShotTimer >= animationTime)
		{
			_oneShotTimer = animationTime;
			_oneShotFinished = true;
		}
		else
		{
			_oneShotTimer += deltatime;
		}
	

	int n = static_cast<int>((_oneShotTimer / animationTime) * frameCount);

	if (n >= frameCount) n = frameCount - 1;
	return n;
}

float Animator::GetAnimationTime(int frameCount, int FPS)
{
	if (FPS <= 0) return 0;

	return (1000.0f / (float)FPS) * frameCount;
}


