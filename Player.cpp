#include "precomp.h"
#include "Player.h"
#include "Animator.h"
#include <iostream>
#include "Camera.h"
#include "CollisionDetection.h"

Player::Player()
{
	InitSprite();
}

void Player::InitSprite()
{
	_idleTorsoSprite = new Sprite(new Surface("assets/Player_Idle_Torso.png"), _idleFrameCount);
	_idleLegSprite = new Sprite(new Surface("assets/Player_Idle_Leg.png"), _idleFrameCount);
	_walkTorsoSprite = new Sprite(new Surface("assets/Player_Walk_Torso.png"), _walkFrameCount);
	_walkLegSprite = new Sprite(new Surface("assets/Player_Walk_Leg.png"), _walkFrameCount);
	_jumpTorsoSprite = new Sprite(new Surface("assets/Player_Jump_Torso.png"), _jumpFrameCount);
	_jumpLegSprite = new Sprite(new Surface("assets/Player_Jump_Leg.png"), _jumpFrameCount);
	_forwardJumpTorsoSprite = new Sprite(new Surface("assets/Player_JumpForward_Torso.png"), _jumpFrameCount);
	_forwardJumpLegSprite = new Sprite(new Surface("assets/Player_JumpForward_Leg.png"), _jumpFrameCount);
	_idleShootSprite = new Sprite(new Surface("assets/Player_Shoot_Idle.png"), _shootFrameCount);
	_walkShootSprite = new Sprite(new Surface("assets/Player_Shoot_Walk.png"), _shootFrameCount);
	_jumpShootSprite = new Sprite(new Surface("assets/Player_Shoot_Jump.png"), _shootFrameCount);
	_crouchShootSprite = new Sprite(new Surface("assets/Player_Crouch_Shoot.png"), _crouchShootFrameCount);
	_crouchIdleSprite = new Sprite(new Surface("assets/Player_Crouch_Idle.png"), _crouchIdleFrameCount);
	_crouchWalkSprite = new Sprite(new Surface("assets/Player_Crouch_Walk.png"), _crouchWalkFrameCount);

	_animatorTorso = new Animator();
	_animatorLeg = new Animator();
	_animatorShoot = new Animator();

	_torsoClips[(int)AnimationState::Idle] = { _idleTorsoSprite, 6, true };
	_torsoClips[(int)AnimationState::Walk] = { _walkTorsoSprite, 24, true };
	_torsoClips[(int)AnimationState::Jump] = { _jumpTorsoSprite, 6, true };
	_torsoClips[(int)AnimationState::JumpForward] = { _forwardJumpTorsoSprite, 6, true };
	_torsoClips[(int)AnimationState::CrouchIdle] = { _crouchIdleSprite, 6, true };
	_torsoClips[(int)AnimationState::CrouchWalk] = { _crouchWalkSprite, 6, true };

	_legClips[(int)AnimationState::Idle] = { _idleLegSprite, 6, true };
	_legClips[(int)AnimationState::Walk] = { _walkLegSprite, 24, true };
	_legClips[(int)AnimationState::IdleShoot] = { _idleLegSprite, 6, true };
	_legClips[(int)AnimationState::WalkShoot] = { _walkLegSprite, 24, true };
	_legClips[(int)AnimationState::Jump] = { _jumpLegSprite, 6, true };
	_legClips[(int)AnimationState::JumpShoot] = { _jumpLegSprite, 6, true };
	_legClips[(int)AnimationState::JumpForward] = { _forwardJumpLegSprite, 6, true };

	_shootClips[(int)AnimationState::IdleShoot] = { _idleShootSprite, 10, false };
	_shootClips[(int)AnimationState::WalkShoot] = { _walkShootSprite, 10, false };
	_shootClips[(int)AnimationState::JumpShoot] = { _jumpShootSprite, 10, false };
	_shootClips[(int)AnimationState::CrouchShoot] = { _crouchShootSprite, 10, false };
}
Player:: ~Player()
{
	delete _animatorTorso;
	delete _animatorLeg;
	delete _animatorShoot;

	delete _idleTorsoSprite;
	delete _idleLegSprite;
	delete _walkTorsoSprite;
	delete _walkLegSprite;
	delete _jumpTorsoSprite;
	delete _jumpLegSprite;
	delete _forwardJumpTorsoSprite;
	delete _forwardJumpLegSprite;
	delete _idleShootSprite;
	delete _walkShootSprite;
	delete _jumpShootSprite;
	delete _crouchShootSprite;
	delete _crouchIdleSprite;
	delete _crouchWalkSprite;
}
void Player::Update(float deltatime)
{
	_previousPosition = _position;

	WalkUpdate(deltatime);
	JumpUpdate(deltatime);
	ShootUpdate();

	LookDirection();
	AnimationStateUpdate();
	UpdateAnimation(deltatime);
}

void Player::Render(Tmpl8::Surface * screen,Camera* camera)
{
	int2 screenPosition = camera->WorldToScreen(_position);

	Sprite* leg = _legClips[(int)_animationState].sprite;
	Sprite* torso = _torsoClips[(int)_animationState].sprite;

	if (leg)   leg->Draw(screen, screenPosition.x, screenPosition.y, _isFacingLeft);
	if (torso) torso->Draw(screen, screenPosition.x, screenPosition.y, _isFacingLeft);

	if (_isShooting)
	{
		Sprite* shoot = _shootClips[(int)_animationState].sprite;
		if (shoot) shoot->Draw(screen, screenPosition.x, screenPosition.y, _isFacingLeft);
	}
}

void Player::UpdateAnimation(float deltatime)
{
	PlayClip(_animatorTorso, _torsoClips[(int)_animationState], deltatime);
	PlayClip(_animatorLeg, _legClips[(int)_animationState], deltatime);

	if (_isShooting)
	{
		PlayClip(_animatorShoot, _shootClips[(int)_animationState], deltatime);
	}
}

void Player::PlayClip(Animator* animator, const AnimationClip& clip, float deltatime)
{
	if (!clip.sprite) return;

	int frame = clip.loop
		? animator->GetFramesLoop(clip.sprite, (int)clip.fps, deltatime)
		: animator->GetFramesOneShot(clip.sprite, (int)clip.fps, deltatime);

	clip.sprite->SetFrame(frame);
}
void Player::SetInputs(float2 movementInput)
{
	_movementInput = movementInput;
}

void Player::JumpUpdate(float deltatime)
{
	_velocityY += GRAVITY * deltatime;
	if (_velocityY > 0.5f) _velocityY = 0.5f;
	if (_jump && _isGrounded)
	{
		_velocityY = -_jumpForce;
		_isGrounded = false;
		_jump = false;
		_isJumping = true;
	}
	_position.y += _velocityY * deltatime;

	//if (_position.y >= groundY)
	//{
	//	_position.y = groundY;
	//	_velocityY = 0;
	//	_isGrounded = true;
	//	_jump = false;
	//	_isJumping = false;
	//}
}

void Player::WalkUpdate(float deltatime)
{

	_isCrouching = _movementInput.y < 0;
	_isMoving = _movementInput.x != 0;

	if (_isCrouching)
	{
		_chosenSpeed = _crouchSpeed;
	}
	else
	{
		_chosenSpeed = _walkSpeed;
	}

	if (_isCrouching && _isShooting) _chosenSpeed = 0;

	_velocityX = _chosenSpeed * deltatime;

	_position.x += _movementInput.x * _velocityX;

}

void Player::ShootUpdate()
{
	if (_shoot)
	{
		//_shootingAnimationFinished = false;
		_isShooting = true;
		_animatorShoot->ResetOneShotTimer();
	}
	_shoot = false;

	if (_isShooting)
	{
		if (_animatorShoot->IsOneShotFinished())
		{
			_isShooting = false;
		}
	}
}

void Player::LookDirection()
{
	if (_movementInput.x != 0)
	{
		if (_movementInput.x > 0)
		{
			_isFacingLeft = false;
		}
		else
		{
			_isFacingLeft = true;
		}
	}
}

void Player::AnimationStateUpdate()
{

	if (_isShooting)
	{
		if (_isCrouching)
		{
			_animationState = AnimationState::CrouchShoot;
		}
		else if (_isMoving)
		{
			_animationState = AnimationState::WalkShoot;
		}
		else
		{
			_animationState = AnimationState::IdleShoot;
		}

		if (_isJumping)
		{
			_animationState = AnimationState::JumpShoot;
		}
	}
	else
	{
		if (_isCrouching)
		{
			if (_isMoving)
			{
				_animationState = AnimationState::CrouchWalk;
			}
			else
			{
				_animationState = AnimationState::CrouchIdle;
			}
		}
		else if (_isMoving)
		{
			_animationState = AnimationState::Walk;
		}
		else
		{
			_animationState = AnimationState::Idle;
		}

		if (_isJumping)
		{
			if (_isMoving)
			{
				_animationState = AnimationState::JumpForward;
			}
			else
			{
				_animationState = AnimationState::Jump;
			}
		}
	}
}


void Player::Jump()
{
	_jump = true;
}

void Player::Shoot()
{
	_shoot = true;
}

void Player::Collision(float2 pushVector)
{
	_position.x += pushVector.x;
	_position.y += pushVector.y;

	if (pushVector.x != 0) _velocityX = 0;
	if (pushVector.y != 0)
	{
		_velocityY = 0;

		if (pushVector.y < 0) 
		{
			_isGrounded = true;
			_isJumping = false;
		}
	}
}


