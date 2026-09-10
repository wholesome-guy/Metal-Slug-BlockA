#pragma once

class Animator;
class Camera;
enum AnimationState { Idle, Walk, Jump, IdleShoot,WalkShoot,JumpShoot,JumpForward, CrouchIdle, CrouchWalk, CrouchShoot, Count };
enum CollisionState { Ground, OneWay,Slope };

struct AnimationClip
{
	Sprite* sprite = nullptr;
	float fps = 0;
	bool loop = false;
};

class Player{

public:

	Player();
	
	virtual ~Player();

	void Update(float deltatime);
	void Render(Tmpl8::Surface* screen,Camera* camera);

	void SetInputs(float2 movementInput);
	void Jump();
	void Shoot();
	void Collision(float2 pushVector, CollisionState collisionState);

	float2 GetPosition() { return _position; }
	float2 GetHitboxPosition() { return { _position.x + _hitboxOffset.x, _position.y + _hitboxOffset.y };}
	int2 GetHitboxSize() { return { _hitboxWidth,_hitboxHeight }; }
	float2 GetPreviousHitbox() { return { _previousPosition.x + _hitboxOffset.x, _previousPosition.y + _hitboxOffset.y }; }
	//void SetHitBoxOffset(int x, int y) { _hitboxOffset.x += x; _hitboxOffset.y += y; }

private:

	void AnimationStateUpdate();
	void UpdateAnimation(float);
	void PlayClip(Animator* animator, const AnimationClip& clip, float deltatime);

	void JumpUpdate(float);
	void WalkUpdate(float);
	void ShootUpdate();

	void LookDirection();
	void InitSprite();


	float2 _position = { 80, 110 };
	float2 _previousPosition = _position;

	float _walkSpeed = 0.15f;
	float _crouchSpeed = 0.05f;
	float _slopeSpeed = 0.06f;
	float _jumpForce = 0.237f;
	float _chosenSpeed = 0;

	float _velocityX = 0;
	float _velocityY = 0;

	bool _jump = false;
	bool _isJumping = false;
	bool _isGrounded = true;

	bool _shoot = false;
	bool _isShooting = false;

	bool _isCrouching = false;
	bool _isMoving = false;
	float2 _movementInput = {0,0};

	bool _isFacingLeft = false;
	AnimationState _animationState = AnimationState::Idle;

	//Collisions
	float2 _hitboxOffset = { 18, 26 };
	int _hitboxWidth = 28;
	int _hitboxHeight = 38;

	int _crouchIdleFrameCount = 7;
	Sprite* _crouchIdleSprite = nullptr;

	int _crouchWalkFrameCount = 7;
	Sprite* _crouchWalkSprite = nullptr;

	int _idleFrameCount = 7;
	Sprite* _idleTorsoSprite = nullptr;
	Sprite* _idleLegSprite = nullptr;

	int _walkFrameCount = 12;
	Sprite* _walkTorsoSprite = nullptr;
	Sprite* _walkLegSprite = nullptr;

	int _jumpFrameCount = 6;
	Sprite* _jumpTorsoSprite = nullptr;
	Sprite* _jumpLegSprite = nullptr;
	Sprite* _forwardJumpTorsoSprite = nullptr;
	Sprite* _forwardJumpLegSprite = nullptr;

	int _shootFrameCount = 10;
	Sprite* _walkShootSprite = nullptr;
	Sprite* _idleShootSprite = nullptr;
	Sprite* _jumpShootSprite = nullptr;

	int _crouchShootFrameCount = 10;
	Sprite* _crouchShootSprite = nullptr;

	Animator* _animatorTorso = nullptr;
	Animator* _animatorLeg = nullptr;
	Animator* _animatorShoot = nullptr;

	AnimationClip _torsoClips[(int)AnimationState::Count];
	AnimationClip _legClips[(int)AnimationState::Count];
	AnimationClip _shootClips[(int)AnimationState::Count];



};

