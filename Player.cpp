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

	_animatorJumpTorso = new Animator();
	_animatorJumpLeg = new Animator();
	_animatorTorso = new Animator();
	_animatorLeg = new Animator();
	_animatorShoot = new Animator();
}
Player:: ~Player()
{
	delete _animatorJumpTorso;
	delete _animatorJumpLeg;
	delete _animatorTorso;
	delete _animatorLeg;
	delete _animatorShoot;
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

	switch (_animationState)
	{
	case AnimationState::Idle:

		_idleLegSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);
		_idleTorsoSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);

		break;
	case AnimationState::IdleShoot:

		_idleLegSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);

		_idleShootSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);

		break;
	case AnimationState::Walk:

		_walkLegSprite->Draw(screen, (int)screenPosition.x , (int)screenPosition.y, _isFacingLeft);

		_walkTorsoSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);

		break; 
	case AnimationState::WalkShoot:

		_walkLegSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);

		_walkShootSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);

		break;
	case AnimationState::Jump:

		_jumpLegSprite->Draw(screen, (int)screenPosition.x , (int)screenPosition.y, _isFacingLeft);

		_jumpTorsoSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);
			break;
	case AnimationState::JumpShoot:

		_jumpLegSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);

		_jumpShootSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);

		break;
	case AnimationState::CrouchIdle:
		_crouchIdleSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);
		break;
	case AnimationState::CrouchWalk:
		_crouchWalkSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);
		break;
	case AnimationState::CrouchShoot:
		_crouchShootSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);
		break;
	case AnimationState::JumpForward:
		_forwardJumpTorsoSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);
		_forwardJumpLegSprite->Draw(screen, (int)screenPosition.x, (int)screenPosition.y, _isFacingLeft);
		break;
	}

}

void Player::UpdateAnimation(float deltatime)
{
	switch (_animationState)
	{
	case AnimationState::Idle:

		_idleTorsoSprite->SetFrame(_animatorTorso->GetFrame(_idleTorsoSprite, 6, deltatime, true));
		_idleLegSprite->SetFrame(_animatorLeg->GetFrame(_idleLegSprite, 6, deltatime, true));


		break;
	case AnimationState::IdleShoot:

		_idleShootSprite->SetFrame(_animatorShoot->GetFrame(_idleShootSprite, 10, deltatime, false, 1));
		_idleLegSprite->SetFrame(_animatorLeg->GetFrame(_idleLegSprite, 6, deltatime, true));

		break;
	case AnimationState::Walk:

		_walkTorsoSprite->SetFrame(_animatorTorso->GetFrame(_walkTorsoSprite, 24, deltatime, true));
		_walkLegSprite->SetFrame(_animatorLeg->GetFrame(_walkLegSprite, 24, deltatime, true));

		break;
	case AnimationState::WalkShoot:

		_walkShootSprite->SetFrame(_animatorShoot->GetFrame(_walkShootSprite, 10, deltatime, false, 1));
		_walkLegSprite->SetFrame(_animatorLeg->GetFrame(_walkLegSprite, 12, deltatime, true));

		break;
	case AnimationState::Jump:

		_jumpTorsoSprite->SetFrame(_animatorJumpTorso->GetFrame(_jumpTorsoSprite, 6, deltatime, true, 1));
		_jumpLegSprite->SetFrame(_animatorJumpLeg->GetFrame(_jumpLegSprite, 6, deltatime, true, 1));

		break;
	case AnimationState::JumpShoot:

		_jumpShootSprite->SetFrame(_animatorShoot->GetFrame(_jumpShootSprite, 6, deltatime, false, 1));
		_jumpLegSprite->SetFrame(_animatorLeg->GetFrame(_jumpLegSprite, 6, deltatime, false));

		break;
	case AnimationState::CrouchIdle:

		_crouchIdleSprite->SetFrame(_animatorTorso->GetFrame(_crouchIdleSprite, 6, deltatime, true));
		break;
	case AnimationState::CrouchWalk:

		_crouchWalkSprite->SetFrame(_animatorTorso->GetFrame(_crouchWalkSprite, 6, deltatime, true));

		break;
	case AnimationState::CrouchShoot:
		_crouchShootSprite->SetFrame(_animatorShoot->GetFrame(_crouchShootSprite, 10, deltatime, false, 1));
		break;
	case AnimationState::JumpForward:
		_forwardJumpTorsoSprite->SetFrame(_animatorTorso->GetFrame(_forwardJumpTorsoSprite, 6, deltatime, false));
		_forwardJumpLegSprite->SetFrame(_animatorLeg->GetFrame(_forwardJumpLegSprite, 6, deltatime, false));
		break;
	}
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
		_isShooting = true;
		_animatorShoot->Reset();
	}
	_shoot = false;

	if (_isShooting)
	{
		if (_animatorShoot->Finished())
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


